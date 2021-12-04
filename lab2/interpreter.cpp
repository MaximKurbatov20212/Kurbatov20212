#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include "interpreter.hpp"
#include "interpreter_error.hpp"
#include "command.hpp"
#include "my_stack.hpp"
#include <map>

bool Interpreter::is_digit(std::string::iterator& it, std::string::iterator& end){
    if(is_negative(it, end)) {return true;}
    return (int)(*it) >= (int)'0' && (int)(*it) <= (int)'9';
}

void Interpreter::get_num(std::string::iterator& it, std::string::iterator& end , MyStack& _stk){
    std::string exp = std::string(it , end);
    std::string::iterator cur_it;

    int shift = exp.find(' ');
    if(shift == -1) cur_it = end;
    else cur_it = exp.begin() + shift;

    std::string str = std::string(it , cur_it);
    std::cout << str << std::endl;
    it = (cur_it == end ? end : cur_it + 1);

    int res = std::stoi(str);  

    _stk.push(res);
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

Command* Interpreter::get_cmd(std::string::iterator& it, std::string::iterator& end){
    std::string str = std::string(it, end);

    std::string::iterator cur_it;
    int shift = str.find(' ');
    if(shift == -1) cur_it = end;
    else cur_it = str.begin() + shift;

    std::string cmd = std::string(it, cur_it);

    it = (cur_it == end ? end : cur_it + 1);

    if(my_creator.find(cmd) != my_creator.end()){
        throw Interpreter_error("no such command");
    }

    return my_creator.find(cmd)->second;        
}

void Interpreter::interpret(std::string& exp){
    result.clear();
    std::string::iterator it = exp.begin();     
    std::string::iterator end = exp.end();

    Context context(_stk, result, it, end);

    bool flag = true;
    while(true){
        try{
            if(is_digit(it,end)) get_num(it, end, _stk);
            else{
                Command* cmd = get_cmd(it,end);
                cmd->apply(context);
            }
        }catch(Interpreter_error& e){
            result.append(e.what());
        }
    }
    //std::cout << _stk;
}