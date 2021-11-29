#include <iostream>
#include <limits>
#include "interpreter.hpp"
#include "interpreter_error.hpp"
#include "command.hpp"
#include "my_stack.hpp"
#include <map>
#include <cassert>

bool Interpreter::is_digit(std::string::iterator& it, std::string::iterator& end){
    if(is_negative(it, end)) {return true;}
    return (int)(*it) >= (int)'0' && (int)(*it) <= (int)'9';
}


long long Interpreter::get_num(std::string::iterator& it, std::string::iterator& end){
    long long res = 0;
    long long deg = 10;
    int k = 1;
    if((*it) == '-'){ k = -1;}
    else {res = (*it) - '0';}
    it++; 
    while(it != end){
        if(is_digit(it,end)){
            res = res * deg + ((*it) - '0'); 
            std::cout << res << std::endl;
            if(res > INT32_MAX){    // доделать
                Interpreter_error("too much number");
            }
        }
        else break;
        it++;
    }
    return res * k;
}

bool Interpreter::is_negative(std::string::iterator& it, std::string::iterator& end){
    if(it + 1 != end && it != end){
        std::string::iterator a = it + 1;
        if(*it == '-' && (int)(*a) >= (int)'0' && (int)(*a) <= (int)'9'){
            return true;
        }
    }
    return false;
}

bool Interpreter::is_cmd(std::string::iterator& it, std::string::iterator& end){
    if(is_negative(it, end)) {return false;}

    if((*it) == '+' || (*it) == '-' || (*it) == '*' || (*it) == '/' || (*it) == '.' || (*it) == '<'|| (*it) == '>'|| (*it) == '=') {return true;}

    if ( (it + 1 != end) && (it + 2 != end)){
        if ((*it) == 'm' && *(it + 1) == 'o' && *(it + 2) == 'd') {return true;}
        if ((*it) == 'd' && *(it + 1) == 'u' && *(it + 2) == 'p') {return true;}
        if ((*it) == 'r' && *(it + 1) == 'o' && *(it + 2) == 't') {return true;}
    }
    if ( (it + 1 != end) && (it + 2 != end) && (it + 3 != end)){
        if ((*it) == 'o' && *(it + 1) == 'v' && *(it + 2) == 'e' && *(it + 3) == 'r'){return true;}
        if ((*it) == 'd' && *(it + 1) == 'r' && *(it + 2) == 'o' && *(it + 3) == 'p'){return true;}
        if ((*it) == 'e' && *(it + 1) == 'm' && *(it + 2) == 'i' && *(it + 3) == 't'){return true;}
        if ((*it) == 's' && *(it + 1) == 'w' && *(it + 2) == 'a' && *(it + 3) == 'p'){return true;}
    }
    return false;
}

long long Interpreter::get_command(std::string::iterator& it, std::string::iterator& end){
    long a = INT32_MAX;
    if ((*it) == '+') {it++; return a + 1;}
    if ((*it) == '-') {it++; return a + 2;}
    if ((*it) == '*') {it++; return a + 3;}
    if ((*it) == '/') {it++; return a + 4;}
    if ((*it) == '.') {it++; return a + 8;}
    if ((*it) == '>') {it++; return a + 14;}
    if ((*it) == '<') {it++; return a + 15;}
    if ((*it) == '=') {it++; return a + 16;}
    if(it + 1 != end && (*it) == 'c' && *(it + 1) == 'r'){ //cr
        it += 2;
        return a + 13;
    }

    if ( (it + 1 != end) && (it + 2 != end)){
        if ((*it) == 'm' && *(it + 1) == 'o' && *(it + 2) == 'd') { //mod
            it += 3;
            return a + 5;
        }
        if ((*it) == 'd' && *(it + 1) == 'u' && *(it + 2) == 'p') { //dup
            it += 3;
            return a + 6;
        }

        if ((*it) == 'r' && *(it + 1) == 'o' && *(it + 2) == 't') { //rot
            it += 3;
            return a + 10;
        }
    }   

    if ( (it + 1 != end) && (it + 2 != end) && (it + 3 != end)){
        if ((*it) == 'o' && *(it + 1) == 'v' && *(it + 2) == 'e' && *(it + 3) == 'r') { //over
            it += 4;
            return a + 11;
        }

        if ((*it) == 'd' && *(it + 1) == 'r' && *(it + 2) == 'o' && *(it + 3) == 'p') { //drop
            it += 4;
            return a + 7;
        }

        if ((*it) == 'e' && *(it + 1) == 'm' && *(it + 2) == 'i' && *(it + 3) == 't') { //emit
            it += 4;
            return a + 12;
        }

        if ((*it) == 's' && *(it + 1) == 'w' && *(it + 2) == 'a' && *(it + 3) == 'p') { //swap
            it += 4;
            return a + 9;
        }
    }  

    return 0;
}

void Interpreter::handle_operand(std::string::iterator & it, std::string::iterator & end){
    long a = get_num(it, end);
    std::cout << "number = " << a << std::endl;
    if(a >= -INT32_MAX && a <= INT32_MAX ){             //operand
        _stk.push((int)a);
        std::cout << _stk;
    }
}

Command* Interpreter::get_cmd(std::string::iterator& it, std::string::iterator & end){
    long long a = get_command(it, end);  
    std::map<int, creator_t>::iterator creator_it = my_creator.find((int)(a - INT32_MAX));            // find command
    creator_t creator = (*creator_it).second;
    return creator(it, end);
}

void Interpreter::interpret(std::string& exp){
    std::string::iterator it = exp.begin();     
    std::string::iterator end = exp.end();

    while(true){
        try{
            if(is_cmd(it, end)) {
                std::cout << "is_cmd " << std::endl;
                Command* cmd = get_cmd(it, end);
                cmd->apply(_stk);
                std::cout << _stk;
            }
            else if(is_digit(it,end)) {
                std::cout << "is_operand" << std::endl;
                handle_operand(it, end);
            }

            else if(it == end)      //we could shift it
                break;

            else {
                it++;
                throw Interpreter_error("unknown symbol");
            }

        }catch(Interpreter_error& e){
            std::cout << e.what() << std::endl;
        }
    }
}
