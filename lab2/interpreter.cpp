#include <iostream>
#include <limits>
#include "interpreter.hpp"
#include "interpreter_error.hpp"
#include "command.hpp"
#include "my_stack.hpp"

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
    return INT32_MAX + 100; // error flag
}

long Interpreter::is_cmd(std::string::iterator& it, std::string::iterator& end){
    if ((*it) == '+') {++(*it); return INT32_MAX + 1;}
    if ((*it) == '-') {++(*it); return INT32_MAX + 2;}
    if ((*it) == '*') {++(*it); return INT32_MAX + 3;}
    if ((*it) == '/') {++(*it); return INT32_MAX + 4;}
    if ( (it + 1 != end) && (it + 2 != end)){
        if ((*it) == 'm' && (*it) == 'o' && (*it) == 'd') {
            (*it) += 3;
            return INT32_MAX + 5;
        }
    }
    return 0;
}

int Interpreter::check(std::string::iterator& it, std::string::iterator& end){
    long lexema = is_cmd(it, end);
    if (lexema != 0){return lexema;}

    lexema = is_num(it, end);
    if (lexema != INT32_MAX + 1 ) return lexema;

    return -INT32_MAX - 1 ; 
}

void Interpreter::handle_operand(std::string::iterator & it, std::string::iterator & end){
    long a = is_num(it, end);
    if(a > INT32_MAX + 5 || a < INT32_MAX + 1){             //operand
        _stk.push((int)a);
    }
    if(a = -INT32_MAX - 1){ throw std::runtime_error("no such command:");}      //error
}

Command* Interpreter::get_cmd(std::string::iterator & it, std::string::iterator & end){
    long a = is_cmd(it, end);
    if(a <= INT32_MAX + 5 && a >= INT32_MAX + 1){     
        std::map<int, creator>::iterator creator_it = my_creator.find((int)(a - INT32_MAX));            // find command
        creator creator = (*creator_it).second;
        return creator(it, end);
    }
}

void Interpreter::interpret(std::string& exp){
    std::string::iterator it = exp.begin();     
    std::string::iterator end = exp.end();

    while(it != end){
        try{
            if(is_cmd(it, end)) {
                Command* cmd = get_cmd(it, end);
                cmd->apply(Interpreter::get_instance()._stk);
            }
            else {handle_operand(it, end);};

        }catch(Interpreter_error& e){
            std::cout << e.what() << std::endl;
        }
    }
}
