#include "stack_dump.hpp"


void stack_dump(int depth, std::ostream& out);

void f1() {
    stack_dump(10, std::cout); 
}

void f2() {
    f1(); 
}

int main() {
    f2();  
    return 0;
}
