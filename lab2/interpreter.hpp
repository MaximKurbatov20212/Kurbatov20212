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
    // Returs always the same instance of interpreter
    static Interpreter& get_instance(){
        static Interpreter i;
        return i;
    }

    std::string interpret(std::string& exp);

    Command* get_cmd(std::string::iterator & it, std::string::iterator & end, Context& context);

    // Register commands 
    bool register_command(const std::string & i, Command* cmd){
        my_commands[i] = cmd;
        return true;
    }

    class MyStack _stk; // after testing will private   

private:
    struct Info{
        int cmds;
        int digits;
        int exceptions;
        void clear(){cmds = 0; digits = 0; exceptions = 0;}
    };
    Info info;
    std::map<std::string, Command*> my_commands; 
    bool is_digit(std::string::iterator& it, std::string::iterator& end);
    void get_num(Context& context);
    bool is_num(std::string& str);
    bool is_negative(std::string::iterator& it, std::string::iterator& end);
    bool is_whitespace(std::string::iterator& it, std::string::iterator& end);
    bool is_print(std::string& cmd, Context& context);
    std::string get_as_str(std::string::iterator& it, std::string::iterator & end);
};
#endif