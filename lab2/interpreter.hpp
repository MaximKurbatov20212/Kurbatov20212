#ifndef INTERPRETER
#define INTERPRETER
#include <iostream>
#include <map>
#include <fstream>
#include <cassert>
#include "my_stack.hpp"
#include "command.hpp"

class Interpreter{
public:
    // Returns always the same instance of interpreter
    static Interpreter& get_instance(){
        static Interpreter i;
        return i;
    }
    // Register commands 
    bool register_command(const std::string & i, Command* cmd){
        my_commands[i] = cmd;
        return true;
    };
    // Gets command
    Command* get_cmd(std::string::iterator & it, std::string::iterator & end);

    std::string interpret(std::string& exp);

    int pop() {
        return _stk.pop();
    }
    void clear() {
        _stk.clear();
    }

private:
    MyStack _stk;
    std::map<std::string, Command*> my_commands; 
    bool is_digit(std::string::iterator& it, std::string::iterator& end);
};
#endif