#include <iostream>
#include "interpreter.hpp"
#include "interpreter_error.hpp"
#include "command.hpp"
#include <map>
#include <algorithm>
#include <string>

Command* Interpreter::get_cmd(std::string::iterator& it, std::string::iterator & end){
    std::string::iterator end_cmd = std::find_if(it, end, [](char i){return std::isspace(i);});
    std::map<std::string, Command*>::iterator command_it = my_commands.find(std::string(it, end_cmd));
    if(command_it == my_commands.end()) throw interpreter_error("no such command");
    it = end_cmd;
    return command_it->second;
}

/*
 * CR: imho good way to right this method:
 * 1. check if given position is a number (we have '-' + digits or just digits and then end of line / space)
 * 2. if not - return false, let get_cmd handle it
 * 3. otherwise stoi and push
 * not insisting though
 */
bool Interpreter::try_get_number(std::string::iterator& it, std::string::iterator& end, Context& context){
    std::string::iterator last_digit;
    if (*it == '-') {
        if (it == end) {
            // CR: please reuse get_cmd: in this case we would get an interpreter_error in case
            // CR: when '-' is not defined for some reason. right now we have ub here
            my_commands.find("-")->second->apply(context);
            it++;
            return true;
        }
        it++;
        last_digit = std::find_if_not(it, end, [](char i){return std::isdigit(i);});
        if (last_digit == it) {
            // CR: same
            // CR: also it is strange that
            // CR: commands "1 2 -." work fine while  "1 2 .." does not. imho it should fail in both cases (please write a test)
            my_commands.find("-")->second->apply(context);
            return true;
        }
        _stk.push(std::stoi(std::string(it - 1, last_digit)));
        it = last_digit;
        return true;
    }
    else if (std::isdigit(*it)){
        last_digit = std::find_if_not(it, end, [](char i){return std::isdigit(i);});
        _stk.push(std::stoi(std::string(it, last_digit)));
        it = last_digit;
        return true;
    }
    return false;
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
            
            if(try_get_number(it, end, context)) continue;

            Command* cmd = get_cmd(it, end);
            if(std::isspace(*it)) it++;
            cmd->apply(context);
        
        }catch(interpreter_error& e){
            context.sstr << e.what();
            context.sstr << '\n';
            return context.sstr.str();
        }catch(std::out_of_range& e){
            context.sstr << "out of range of int\n";
            return context.sstr.str();
        }
        catch(std::exception& e){
            // CR: i think it's better to just not catch exception e. because this way it'll just end up in cerr
            // CR: and user will get much more info from stacktrace then from failed assert
            assert(false);
        }
    }
    //std::cout << _stk;
    context.sstr << "< ok\n";
    return context.sstr.str();
}