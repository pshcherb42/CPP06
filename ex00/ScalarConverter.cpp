#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { 
	(void)other;
	return *this;
}


// helper functions

// detect type
static bool isCharType(const std::string& input) {
	/*if (input.length() == 1) {
		return true;
	}*/
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'') {
		return true;
	}
	// Handle escape sequences like "\n", "\t", "\0", etc.
	if (input.length() == 2 && input[0] == '\\') {
		char second = input[1];
		return (second == 'n' || second == 't' || second == 'r' || 
				second == 'b' || second == 'f' || second == 'v' || 
				second == 'a' || second == '0' || second == '\\');
	}
	return false;
}

static bool isIntType(const std::string& input) {
	if (input.empty())
		return false;
	
	size_t start = 0;
	if (input[0] == '-' || input[0] == '+') {
		if (input.length() == 1)
			return false;
		start = 1;
	}

	for (size_t i = start; i < input.length(); i++) {
		if (!isdigit(input[i]))
			return false;
	}

	return true;
}
 // extract
static int extractInt(const std::string& input) {
	try {
		return std::stoi(input);
	} catch (const std::out_of_range& e) {
		throw std::invalid_argument("Integer out of range");
	}
}

static char extractChar(const std::string& input) {
	/*if (input.length() == 1) {
		return input[0];
	}*/
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'') {
		return input[1];
	}
	// Handle escape sequences
	if (input.length() == 2 && input[0] == '\\') {
		switch (input[1]) {
			case 'n': return '\n';
			case 't': return '\t';
			case 'r': return '\r';
			case 'b': return '\b';
			case 'f': return '\f';
			case 'v': return '\v';
			case 'a': return '\a';
			case '0': return '\0';
			case '\\': return '\\';
		}
	}
	throw std::invalid_argument("Not a valid character");
}

void ScalarConverter::convert(std::string input) {
	// Detect and convert based on type
	if (isCharType(input)) {
		try {
			char c = extractChar(input);
		// Convert char to all types
			if (std::isprint(c)) {
		   		std::cout << "char: '" << c << "'" << std::endl;
			} else {
				throw std::invalid_argument ("char: Non displayable");
			}
			std::cout << "int: " << static_cast<int>(c) << std::endl;
			std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
			std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;	
		} catch (const std::invalid_argument& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	else if (isIntType(input)) {
		try {
			int n = extractInt(input);
			
			// Convert int to all types
			// Check if int can be displayed as char
			if (n >= 0 && n <= 127 && std::isprint(static_cast<char>(n))) {
				std::cout << "char: '" << static_cast<char>(n) << "'" << std::endl;
			} else {
				std::cout << "char: Non displayable" << std::endl;
			}
			
			std::cout << "int: " << n << std::endl;
			std::cout << "float: " << static_cast<float>(n) << ".0f" << std::endl;
			std::cout << "double: " << static_cast<double>(n) << ".0" << std::endl;
			
		} catch (const std::out_of_range& e) {
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
		}
	}
	else {
		std::cout << "Type not recognized or not implemented yet" << std::endl;
	}
}

ScalarConverter::~ScalarConverter() {}