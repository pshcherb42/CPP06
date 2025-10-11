#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main() {
    Base* obj = generate();

    identify(obj);
    identify(*obj);
}