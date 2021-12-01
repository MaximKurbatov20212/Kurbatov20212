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

    // Handles string, finds lexems(operands/commands) 
    // Throws custom exeptions and catchs them
    // Exception  "no such command", if user entered uncorrect data
    // Exception  "out of range of int", if user entered too much/low number   
    // Exception  "unkown symbol" if you entered an incorrect oprand
    // Exception  "division by zero"  
    // Exception  "there is no second "" if you entered ."sample
    // Exception  "no elements" if stack is empty
    // Exception  "too few elements" if command cannot be applied
    void interpret(std::string& exp);

    // Returns suitible command    
    Command* get_cmd(std::string::iterator & it, std::string::iterator & end);

    typedef Command*(*creator_t)();    // ptr to function(Ctor different commands)

    // Registers commands 
    bool register_command(int i, creator_t cmd){    
        my_creator[i] = cmd;
        return true;
    }


    // for testing

    std::string get_result(){return result;}
        
    std::string result;

    class MyStack _stk; // after testing will private

private:
    struct Info{
        int c_cmd;
        int c_operands;
        int c_exep;
        bool is_print;
        bool is_cr;
        bool is_point_or_emit;
        
        void clear(){c_cmd = 0; c_operands = 0; c_exep = 0;
                    is_print = false; is_cr = false; is_point_or_emit = false;
        }
    };

    Info info;
    std::map<int, creator_t> my_creator; 
    void handle_operand(std::string::iterator & it, std::string::iterator & end);
    bool is_digit(std::string::iterator& it, std::string::iterator& end);
    long long get_num(std::string::iterator& it, std::string::iterator& end);
    bool is_cmd(std::string::iterator& it, std::string::iterator& end);
    long long get_command(std::string::iterator& it, std::string::iterator& end);
    bool is_negative(std::string::iterator& it, std::string::iterator& end);
    void handle_cmd(std::string::iterator& it, std::string::iterator & end);
};
#endif