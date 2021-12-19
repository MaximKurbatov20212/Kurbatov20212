#include <iostream>
#include "interpreter.hpp"
#include "interpreter_error.hpp"
#include "command.hpp"
#include <map>
#include <algorithm>
#include <string>

inline bool Interpreter::is_digit(std::string::iterator& it, std::string::iterator& end){
    return((*it == '-' && it + 1 != end && std::isdigit(*(it + 1))) || std::isdigit(*it));
}

Command* Interpreter::get_cmd(std::string::iterator& it, std::string::iterator & end){
    std::string::iterator end_cmd = std::find_if(it, end, [](char i){return std::isspace(i);});
    std::map<std::string, Command*>::iterator command_it = my_commands.find(std::string(it, end_cmd));
    if(command_it == my_commands.end()) throw interpreter_error("no such command\n");
    it = end_cmd;
    return command_it->second;
}

std::string Interpreter::interpret(std::string& exp){
    std::string::iterator it = exp.begin();
    std::string::iterator end = exp.end();
    Context context(_stk, it , end);
    while(it != end){
        try{
            if(std::isspace(*it)) {
                it++;
                continue;
            }

            if(is_digit(it, end)) { // finish up
                std::string::iterator start = it;
                if(*it == '-') it++;
                auto end_digit = std::find_if(it, end, [](char i){return !std::isdigit(i);});
                it = end_digit;
                _stk.push(std::stoi(std::string(start, end_digit)));
            }
            else{
                Command* cmd = get_cmd(it, end);
                if(std::isspace(*it)) it++;
                cmd->apply(context);
            }
        }catch(interpreter_error& e){
            context.sstr << e.what();
            return context.sstr.str();
        }catch(std::out_of_range& e){
            context.sstr << "out of range of int\n";
            return context.sstr.str();
        }
    }
    context.sstr << "< ok\n";
    return context.sstr.str();
}