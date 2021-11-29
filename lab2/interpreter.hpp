#ifndef INTERPRETER
#define INTERPRETER

#include<iostream>
#include<map>
#include"command.hpp"

class Interpreter{
public:
    static Interpreter& get_instance(){
        static Interpreter i;
        return i;
    }

    typedef Command* (*creator)(std::string::iterator& it, std::string::iterator& end);    // ptr to function(Ctor different commands)

    bool register_command(int i, creator cmd){    
        my_creator[i] = cmd;
        return true;
    }

    void interpret(std::string& exp);
    
    Command* get_cmd(std::string::iterator & it, std::string::iterator & end);

    void handle_operand(std::string::iterator & it, std::string::iterator & end);

    class MyStack _stk;
private:
    std::map<int, creator> my_creator; 
    int check(std::string::iterator& it, std::string::iterator& end);
    bool is_digit(std::string::iterator& it);
    long is_num(std::string::iterator& it, std::string::iterator& end);
    long is_cmd(std::string::iterator& it, std::string::iterator& end);
};
#endif