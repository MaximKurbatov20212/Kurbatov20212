#ifndef INTERPRETER
#define INTERPRETER

#include <iostream>
#include <map>
#include "my_stack.hpp"
#include "command.hpp"

class Interpreter{
public:
    static Interpreter& get_instance(){
        static Interpreter i;
        return i;
    }

    void interpret(std::string& exp);
    
    Command* get_cmd(std::string::iterator & it, std::string::iterator & end);

    typedef Command*(*creator_t)(std::string::iterator& it, std::string::iterator& end);    // ptr to function(Ctor different commands)

    bool register_command(int i, creator_t cmd){    
        my_creator[i] = cmd;
        return true;
    }

    void handle_operand(std::string::iterator & it, std::string::iterator & end);

    class MyStack _stk;
private:
    std::map<int, creator_t> my_creator; 
    bool is_digit(std::string::iterator& it, std::string::iterator& end);
    long long get_num(std::string::iterator& it, std::string::iterator& end);
    bool is_cmd(std::string::iterator& it, std::string::iterator& end);
    long long get_command(std::string::iterator& it, std::string::iterator& end);
    bool is_negative(std::string::iterator& it, std::string::iterator& end);
};
#endif