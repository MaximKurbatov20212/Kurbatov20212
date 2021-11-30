#ifndef INTERPRETER
#define INTERPRETER

#include <iostream>
#include <map>
#include "my_stack.hpp"
#include "command.hpp"

class Interpreter{
public:
    // Returs always the same instance of interpreter
    static Interpreter& get_instance(){
        static Interpreter i;
        return i;
    }

    // Handles string, finds lexems(operands/commands) 
    // Throws exception "no such command", if user entered uncorrect data
    // Throws exception "out of range of int", if user entered too much/low number
    void interpret(std::string& exp);

    // Returns suitible command    
    Command* get_cmd(std::string::iterator & it, std::string::iterator & end, bool& flag);

    typedef Command*(*creator_t)();    // ptr to function(Ctor different commands)

    // Registers commands
    bool register_command(int i, creator_t cmd){    
        my_creator[i] = cmd;
        return true;
    }

private:
    class MyStack _stk;
    std::map<int, creator_t> my_creator; 
    void handle_operand(std::string::iterator & it, std::string::iterator & end);
    bool is_digit(std::string::iterator& it, std::string::iterator& end);
    long long get_num(std::string::iterator& it, std::string::iterator& end);
    bool is_cmd(std::string::iterator& it, std::string::iterator& end);
    long long get_command(std::string::iterator& it, std::string::iterator& end);
    bool is_negative(std::string::iterator& it, std::string::iterator& end);
};
#endif