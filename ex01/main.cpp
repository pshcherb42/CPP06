#include "Serializer.hpp"

int main() {
    struct Data d = {0, 1};

   // struct Data* ptr = &d;

    uintptr_t ui = Serializer::serialize(&d);

    std::cout << "Data *ptr address : " << &d << std::endl;
    std::cout << "Deserialize return : " <<  Serializer::deserialize(ui) << std::endl;
}