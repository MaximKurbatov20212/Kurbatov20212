#ifndef INTERPRETER
#define INTERPRETER

#include <iostream>
#include <map>
#include <fstream>
#include "my_stack.hpp"
#include "command.hpp"
#include <cassert>

class Interpreter{
public:
    // Returs always the same instance of interpreter
    static Interpreter& get_instance(){
        static Interpreter i;
        return i;
    }

    std::string interpret(std::string& exp);
  
    Command* get_cmd(std::string::iterator & it, std::string::iterator & end);

    typedef Command*(*creator_t)();    // ptr to function(Ctor different commands)

    // Registers commands 
    bool register_command(std::string i, Command* cmd){    
        my_creator[i] = cmd;
        return true;
    }

    //struct Context context;
    class MyStack _stk; // after testing will private
    
private:
    struct Info{
        int cmds;
        int digits;
        int exept;
        void clear(){
            cmds = 0;
            digits = 0;
            exept = 0;
        }
    };
    Info info;
    std::map<std::string, Command*> my_creator; 
    bool is_digit(std::string::iterator& it, std::string::iterator& end);
    void get_num(Context& context);
    bool is_negative(std::string::iterator& it, std::string::iterator& end);
};
#endif