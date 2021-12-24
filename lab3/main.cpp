#include "any.hpp"
#include <any>

int main(){
    int a1 = 2;
    utils::Any c = a1;
    std::cout << (typeid(any_cast<int>(c)) == typeid(int*)) << std::endl;
    
    int* a = new int(12);
    std::any A = a;
    std::cout << (typeid(std::any_cast<int*>(A)) == typeid(int*)) << std::endl;
    std::cout << std::any_cast<int*>(A) << std::endl;

}