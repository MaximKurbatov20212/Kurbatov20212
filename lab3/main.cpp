#include "any.hpp"

int main(){
    int* p = new int(5);
    
    utils::Any b2 = p;
    utils::Any a2 = b2;

    std::cout << *(utils::any_cast<int*>(&b2)) << std::endl;
    
    delete p;
}