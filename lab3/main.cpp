#include "any.hpp"
#include <any>
class Point{
public:
    int x = 0;
    int y = 0;
};

int main(){
    std::string v3 = "hello";
    utils::Any a3 = v3;
    utils::Any a4 = a3;
    std::cout << (a3.type() == typeid(std::string)) << std::endl;
    std::cout << (a3.get_value<std::string>() == "hello")  << std::endl;;
}