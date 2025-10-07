#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
#include <string>
#include <iostream>

class ScalarConverter {
    private:
        ScalarConverter();
    public:
        ScalarConverter(const ScalarConverter& other);
        ScalarConverter& operator=(const ScalarConverter& other);

        // static functions can be used without creating class object
        // they only have access to static data memebers or other static functions
        // they are useful when the logic of the function is independent from object state
        static void convert(std::string input);

        ~ScalarConverter();
};

#endif