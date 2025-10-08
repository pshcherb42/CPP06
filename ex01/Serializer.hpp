#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP
#include "Data.hpp"
#include <stdint.h>
#include <iostream>

class Serializer {
	private:
		Serializer();
	public:
		Serializer(const Serializer& other);
		Serializer& operator=(const Serializer& other);

		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);

		~Serializer();
};

#endif