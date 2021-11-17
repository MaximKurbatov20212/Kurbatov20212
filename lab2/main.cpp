#include <iostream>
#include <stack>
#include "interpreter.hpp"

int main(){
    std::string exp;
    Interpreter interpreter = Interpreter::get_instance();
    
    while(true){
        std::cout << ">";
        std::cin >> exp;
        interpreter.interpret(exp);
    }
    return 0;
}