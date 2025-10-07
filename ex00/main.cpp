#include "ScalarConverter.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <value>" << std::endl;
		return 1;
	}
	
	// detect type passed as argv[1]
	ScalarConverter::convert(argv[1]);

	// convert it from string to its actual type
}