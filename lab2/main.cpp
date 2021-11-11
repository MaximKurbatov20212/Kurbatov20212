#include <iostream>
#include <stack>

int main(){

    std::string exp;
    Interpreter interpreter;

    while(true){
        std::cout << ">";
        std::cin >> exp;
        interpreter.interpret(exp);
    }
    return 0;
}