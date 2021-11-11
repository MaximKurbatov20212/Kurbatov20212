#include <iostream>
#include "interpreter.hpp"
#include <stack>

bool Interpreter::is_num(std::string& exp){
    size_t len = exp.length();
    for(int i = 0 ; i < len ; i++){
        if(!is_digit(exp[i])){
            return false;
        }
    }
    return true;
} 


bool Interpreter::is_cmd(std::string& exp){
    if( exp == "+" ||  exp == "-" || exp == "/" || exp == "*" || exp == "mod"
        || exp == "dup" || exp == "drop" || exp == "swap" || exp == "rot" || exp == "over"   
        || exp == "emit" || exp == "cr" )
        return true;
    return false;    
}

void Interpreter::interpret(std::string& exp){
    if(is_num(exp)){
        stk_.push();
        
    }
}