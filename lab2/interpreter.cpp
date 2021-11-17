#include <iostream>
#include "interpreter.hpp"
#include "interpreter_error.hpp"
#include "command.hpp"
#include <limits>
#include <stack> 

bool Interpreter::is_digit(std::string::iterator& it){
    return (int)(*it) > (int)'1' && (int)(*it) < (int)'9';
}

long Interpreter::is_num(std::string::iterator& it, std::string::iterator& end){
    long res = 0;
    int deg = 1;
    if(is_digit(it)) {
        res = (int)(*it);
        do{
            if(is_digit(it)){
                res += (*it) * deg;
                deg *= 10;
                if(res > INT32_MAX){
                    std::cout << "too much number" << std::endl;
                }
            }
        }while(it != end);
        return res;
    }
    return INT32_MAX + 1; // error flag
}

long Interpreter::is_cmd(std::string::iterator& it, std::string::iterator& end){
    if ((*it) == '+') return INT32_MAX + 2;
    if ((*it) == '-') return INT32_MAX + 3;
    if ((*it) == '*') return INT32_MAX + 4;
    if ((*it) == '/') return INT32_MAX + 5;
    if ( (it + 1 != end) && (it + 2 != end)){
        if ((*it) == 'm' && (*it) == 'o' && (*it) == 'd') return INT32_MAX + 6;
    }
    return 0;
}

int Interpreter::check(std::string::iterator& it, std::string::iterator& end){
    if (is_cmd(it, end))            return 1;
    if (is_num(it, end) != INT32_MAX + 1 ) return 2;
    return 0; 
}

auto get_cmd(std::string::iterator & it, std::string::iterator & end){
    
    std::cout << "no such command: '" << *it << "'";
}

void Interpreter::interpret(std::string& exp){
    std::string::iterator it = exp.begin();
    std::string::iterator end = exp.end();
    while(it != end){
        try{
            Command * cmd = get_cmd(it, end);
        }catch(Interpreter_error& e){
            std::cout << e.what() << std::endl;
        }
    }
}
