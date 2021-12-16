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
    // CR: just use std::find_if(it, end, std::iswspace)
    // CR: because line start (.") should always have a space after.
    // CR: same goes for command name (it may also have end_of_line afterwards, but this case is covered here also)
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

            if(is_digit(it, end)) {
                std::string::iterator start = it;
                // CR: we already know this information, we can rewrite this if so we would check it once
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

            // CR: i think we can just catch any exception here and do not handle logic_error at line 54
        }catch(Interpreter_error& e){
            context.sstr << e.what();
            flag = true;
            // CR: i think we should stop executing current line with commands if exception occurred
            // CR: the reason is that commands after failed command probably rely on previous results
        }
    }
    if (!flag) context.sstr << "< ok\n";
    return context.sstr.str();
    /*
     * CR: in general I'd expect here something like (pseudocode):
     * try {
     * while (it != end) {
     *  if (is_wspace(it)) {
     *    it++;
     *    continue;
     *  }
     *  if (is_number_start(it)) {
     *      int number = parse_number(it);
     *      // iterator already moved in get_digit
     *      stk_.push(number);
     *      continue;
     *  }
     *  Command * cmd = parse_cmd(it, end);
     *  if (cmd == nullptr) {
     *      context.sstr << "command not found";
     *      return context.sstr.str();
     *  }
     *  cmd->apply(context);
     *  // iterator already moved in parse_cmd
     * }
     * } catch (exception & e) {
     *  context.sstr << e.what() << std::endl;
     *  return context.sstr.str();
     * }
     * context.sstr << "\n ok";
     * return context.sstr.str()
     */
}