#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <iomanip>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { 
	(void)other;
	return *this;
}
// helper functions

// detect type
static bool isCharType(const std::string& input) {
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'') { // 'a' 'b' 'A' '4'
		if (isdigit(input[1])) // '5' '6' '='
			return false;
		if (!isalpha(input[1]))
			return false;
		return true;
	}
	//std::cout << "NOT char" << std::endl;
	return false;
}

static bool isIntType(const std::string& input) {
	//std::cout << "is int?" << std::endl;
	size_t start = 0;
	if (input[0] == '-' || input[0] == '+')
		start = 1;
	for (size_t i = start; i < input.length(); i++) {
		//std::cout << "inside for loop" << std::endl;
		if (!isdigit(input[i])) {
			//std::cout << "NOT int" << std::endl;
			return false;
		}
		//std::cout << "end of loop" << std::endl;
	}
	//std::cout << "outside for loop" << std::endl;
	return true;
}

static bool isFloatType(const std::string& input) {
	//std::cout << "is float?" << std::endl;
	if (input == "-inff" || input == "+inff" || input == "nanf")
		return true;
	size_t start = 0;
	int count = 0;
	if (input[0] == '-' || input[0] == '+') 
		start = 1;
	if (input.back() != 'f') 
		return false;
	if (input.find('f') != input.size() - 1)
        return false;
	if (!isdigit(input[start])) // ".05f"
		return false;
	//std::cout << "first sign is digit" << std::endl;
	for (size_t i = start; i < input.length() - 1; i++) {
		if (!isdigit(input[i])) { // "0.5f"
			if (input[i] == '.') // "0..5f" "0.50.f"
				count++;
			else
				return false;
		}
	}
	if (count != 1)
		return false;
	return true;
}

static bool isDoubleType(const std::string& input) {
	//std::cout << "is float?" << std::endl;
	if (input == "-inf" || input == "+inf" || input == "nan")
		return true;

	// Reject if it contains 'f' (it's a float, not a double)
    if (input.find('f') != std::string::npos)
        return false;
	
	size_t start = 0;
	int count = 0;
	if (input[0] == '-' || input[0] == '+') 
		start = 1;
	if (!isdigit(input[start])) // ".05f"
		return false;
	//std::cout << "first sign is digit" << std::endl;
	for (size_t i = start; i < input.length(); i++) {
		if (!isdigit(input[i])) { // "0.5f"
			if (input[i] == '.') // "0..5f" "0.50.f"
				count++;
			else
				return false; // reject invalid characters
		}
	}
	if (count != 1)
		return false;
	return true;	
}

 // extract

static char extractChar(const std::string& input) {
	return static_cast<char>(input[1]);
}

static int extractInt(const std::string& input) {
	return std::stoi(input);
}

static float extractFloat(const std::string& input) {
	return std::stof(input);
}

static double extractDouble(const std::string& input) {
	return std::stod(input);
}

void ScalarConverter::convert(std::string input) {
	// detect type passed as argv[1]
	// convert it from string to its actual type
	if (isCharType(input)) {
		// std::cout << "input is a char" << std::endl;
		char c = extractChar(input);
		std::cout << "char : " << c << std::endl;
		std::cout << "int : " << static_cast<int>(c) << std::endl;
		std::cout << "float : " << static_cast<float>(c) << std::endl;
		std::cout << "double : " << static_cast<double>(c) << std::endl;
	}
	else if (isIntType(input)) {
		//std::cout << "input is int" << std::endl;
		int n = extractInt(input);
		try {
			if (n < 0 || n > 255)
				throw std::out_of_range("impossible");
			if (!isprint(static_cast<char>(n)))
				throw std::out_of_range("not printable");
			else
				std::cout << "char : " << static_cast<char>(n) << std::endl;
		} catch (std::out_of_range e) {
			std::cout << "char : " << e.what() << std::endl;
		}
		std::cout << "int : " << n << std::endl;
		std::cout << "float : " << std::fixed << std::setprecision(1) << static_cast<float>(n) << "f" << std::endl;
		std::cout << "double : " << std::fixed << std::setprecision(1) << static_cast<double>(n) << std::endl;
	}
	else if (isFloatType(input)) {
		//std::cout << "input is float" << std::endl;
		float f = extractFloat(input);
		try {
			if (f < 0 || f > 255)
				throw std::out_of_range("impossible");
			if (input == "-inff" || input == "+inff" || input == "nanf")
				throw std::out_of_range("impossible");
			else if (!isprint(static_cast<char>(f)))
				throw std::out_of_range("not printable");
			else
				std::cout << "char : " << static_cast<char>(f) << std::endl;
		} catch (std::out_of_range e) {
			std::cout << "char : " << e.what() << std::endl;
		}
		try {
			if (input == "-inff" || input == "+inff" || input == "nanf")
				throw std::out_of_range("impossible");
			else
				std::cout << "int : " << static_cast<int>(f) << std::endl;
		} catch (std::out_of_range e) {
			std::cout << "int : " << e.what() << std::endl;
		}
		std::cout << "float : " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
		std::cout << "double : " << std::fixed << std::setprecision(1) << static_cast<double>(f) << std::endl;
	}
	else if (isDoubleType(input)) {
		//std::cout << "input is double" << std::endl;
		double d = extractDouble(input);
		try {
			if (d < 0 || d > 255)
				throw std::out_of_range("impossible");
			if (input == "-inf" || input == "+inf" || input == "nan")
				throw std::out_of_range("impossible");
			else if (!isprint(static_cast<char>(d)))
				throw std::out_of_range("not printable");
			else
				std::cout << "char : " << static_cast<char>(d) << std::endl;
		} catch (std::out_of_range e) {
			std::cout << "char : " << e.what() << std::endl;
		}
		try {
			if (input == "-inf" || input == "+inf" || input == "nan")
				throw std::out_of_range("impossible");
			else
				std::cout << "int : " << static_cast<int>(d) << std::endl;
		} catch (std::out_of_range e) {
			std::cout << "int : " << e.what() << std::endl;
		}
		std::cout << "float : " << std::fixed << std::setprecision(1) << static_cast<float>(d) << "f" << std::endl;
		std::cout << "double : " << std::fixed << std::setprecision(1) << d << std::endl;
	}
}

ScalarConverter::~ScalarConverter() {}