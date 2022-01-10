#include "any.hpp"

int main(){
    utils::Any a2(5);

    std::cout << utils::any_cast<double>(&a2) << std::endl;
}