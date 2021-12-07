#include <iostream>
#include <limits>
#include "interpreter.hpp"
#include "interpreter_error.hpp"
#include "command.hpp"
#include "my_stack.hpp"
#include <map>

bool Interpreter::is_digit(std::string::iterator& it, std::string::iterator& end){
    if(is_negative(it, end)) return true;
    return (int)(*it) >= (int)'0' && (int)(*it) <= (int)'9';
}

bool Interpreter::is_num(std::string& str){
    int k = (str[0] == '-'); // if number is negative
    int len = str.length();
    for(int i = k; i < len; i++){
        if (!isdigit(str[i])) 
            return false;
    }
    return true;
}

std::string Interpreter::get_as_str(std::string::iterator& it, std::string::iterator & end){
    std::string str = std::string(it, end); // Ctor
    std::string::iterator cur_it;

    int shift = str.find(' ');
    if(shift == -1) cur_it = end;           // if could not find whitespace
    else cur_it = it + shift;               // jump to next whitespace

    std::string cmd = std::string(it, cur_it); // make command
    it = (end == cur_it ? end : cur_it + 1);   
    return cmd;
}

void Interpreter::get_num(Context& context){
    std::string number = get_as_str(context.it, context.end);

    if(is_num(number)) _stk.push(std::stoi(number));
    else Interpreter_error("no such command\n");
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

bool Interpreter::is_whitespace(std::string::iterator& it, std::string::iterator& end){
    if(it != end && *it == ' ') {
        it++;
        return true;
    }
    return false;
}

bool Interpreter::is_print(std::string& cmd, Context& context){
    int len = cmd.length();
    if((cmd[0] = '.') && (cmd[1] == '\"') && (len > 3)) {
        if(cmd[len - 1] == '\"'){
            context.str = cmd;
            return true;
        }
        throw Interpreter_error("closing bracket is missing\n");
    }
    return false;
}

Command* Interpreter::get_cmd(std::string::iterator& it, std::string::iterator & end, Context& context){
    std::string cmd = get_as_str(it, end);

    if(my_commands.find(cmd) == my_commands.end()){
        
        if(is_print(cmd, context)) return my_commands.find(".\"")->second; // this command is not separated by a space from the operands
        
        throw Interpreter_error("no such command\n");
    }

    std::map<std::string, Command*>::iterator command_it = my_commands.find(cmd);
    return command_it->second;
}

std::string Interpreter::interpret(std::string& exp){
    std::string::iterator it = exp.begin();     
    std::string::iterator end = exp.end();

    Context context(_stk, it , end);
    context.sstr.clear();

    while(it != end){
        try{
            if(is_whitespace(it, end)) continue;
            
            if(is_digit(it, end)) {
                get_num(context);
                info.digits += 1;
            }
            
            else{
                Command* cmd = get_cmd(it, end, context);
                cmd->apply(context);
                info.cmds += 1;
            }

        }catch(Interpreter_error& e){
            context.sstr << e.what();
            info.exceptions += 1;
        }

        catch(std::logic_error& e){     // std::stoi
            context.sstr << "out of range of int\n";
            info.exceptions += 1;
        }
    }
    if(info.exceptions == 0 && info.cmds == 0 && info.digits != 0) context.sstr << "< ok\n"; 
    info.clear();
    std::cout << context.stk;
    return context.sstr.str();
}