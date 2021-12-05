#include <iostream>
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

void Interpreter::get_num(Context& context){

    std::string exp = std::string(context.it , context.end);
    std::string::iterator cur_it;
    int shift = exp.find(' ');
    if(shift == -1) cur_it = context.end;
    else cur_it = context.it + shift;

    std::string str = std::string(context.it , cur_it);

    context.it = (cur_it == context.end ? context.end : cur_it + 1);

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

Command* Interpreter::get_cmd(std::string::iterator& it, std::string::iterator & end){

    std::string str_ = std::string(it, end);

    std::string::iterator cur_it;

    int shift = str_.find(' ');
    if(shift == -1) cur_it = end;

    else cur_it = it + shift;

    std::string cmd = std::string(it, cur_it);

    if(cmd == " ") it++;

    it = (end == cur_it ? end : cur_it + 1);

    if(my_creator.find(cmd) == my_creator.end()) throw Interpreter_error("no such command\n");

    std::map<std::string, Command*>::iterator creator_it = my_creator.find(cmd);
    return creator_it->second;
}

std::string Interpreter::interpret(std::string& exp){
    std::string::iterator it = exp.begin();     
    std::string::iterator end = exp.end();

    Context context(_stk, it , end);
    
    context.sstr.clear();

    while(true){
        try{
            if(*it == ' ') {
                it++;
                continue;
            }

            if(is_digit(it, end)) {
                get_num(context);
                info.digits += 1;
                //std::cerr << _stk << std::endl;  
            }
            else{

                Command* cmd = get_cmd(it, end);
                cmd->apply(context);
                info.cmds += 1;
            }
            
            if(it == end) break;

        }catch(Interpreter_error& e){
            context.sstr << e.what();
            info.exept += 1;
            if(it == end) break;
        }
    }
    if(info.exept == 0 && info.cmds == 0 && info.digits != 0) context.sstr << "< ok\n"; 
    info.clear();
    
    return context.sstr.str();
}