#include <iostream>
#include <stack>
#include <cstring>
#include "interpreter.hpp"
#include "command.hpp"

int main(){
    std::string exp;
    Interpreter interpreter = Interpreter::get_instance();

    while(true){
        std::cout << "> ";
        std::getline(std::cin , exp);
        interpreter.interpret(exp);
    }
    return 0;
}