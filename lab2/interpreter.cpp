#include <iostream>
#include "interpreter.hpp"
#include "interpreter_error.hpp"
#include "command.hpp"
#include "my_stack.hpp"
#include <map>
#include <algorithm>
#include <string>

inline bool Interpreter::is_digit(std::string::iterator& it, std::string::iterator& end){
    return((*it == '-' && it + 1 != end && std::isdigit(*(it + 1))) || std::isdigit(*it));
}

std::string Interpreter::get_as_str(std::string::iterator& it, std::string::iterator & end){
    auto cur_it = std::find(it, end, ' ');    
    std::string cmd = std::string(it, cur_it);
    it = cur_it;   
    return cmd;
}

inline bool Interpreter::is_print(std::string::iterator& it, std::string::iterator& end){
    return ((*it == '.') && ((it + 1) != end) && (*(it + 1) == '\"'));
}

Command* Interpreter::get_cmd(std::string::iterator& it, std::string::iterator & end){
    if(is_print(it, end)) return my_commands.find(".\"")->second;

    std::string cmd = get_as_str(it, end);
    std::map<std::string, Command*>::iterator command_it = my_commands.find(cmd);

    if(command_it == my_commands.end()) throw Interpreter_error("no such command\n");
    return command_it->second;
}

std::string Interpreter::interpret(std::string& exp){
    std::string::iterator it = exp.begin();     
    std::string::iterator end = exp.end();
    Context context(_stk, it , end);
    bool flag = false;
    while(it != end){
        try{
            if(std::isspace(*it)) {
                it++;
                continue;
            }

            else if(is_digit(it, end)) {
                std::string::iterator start = it;
                if(*it == '-') it++;
                auto end_digit = std::find_if_not(it, end, [](char i){return std::isdigit(i);});
                it = end_digit;
                try {
                    _stk.push(std::stoi(std::string(start, end_digit)));
                }catch(std::logic_error& e) {
                    throw Interpreter_error("out of range of int\n");
                }
            }
            else{
                Command* cmd = get_cmd(it, end);
                cmd->apply(context);
            }

        }catch(Interpreter_error& e){
            context.sstr << e.what();
            flag = true;
        }
    }  
    if (flag == false) context.sstr << "< ok\n";
    else flag = false;
    //std::cout << context.stk;
    return context.sstr.str();
}