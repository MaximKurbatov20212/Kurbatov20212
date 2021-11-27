#include<iostream>
#include "command.hpp"
#include "interpreter.hpp"

namespace{
    Command* add_creator(std::string::iterator & it, std::string::iterator & end){
        return new Add();
    }
    
    bool add_cmd = Interpreter::get_instance().register_command(1, add_creator(it, end));

    Command* sub_creator(std::string::iterator & it, std::string::iterator & end){
        return new Sub();
    }
    bool sub_cmd = Interpreter::get_instance().register_command(2, sub_creator(it, end));

    Command* mul_creator(std::string::iterator & it, std::string::iterator & end){
        return new Mul();
    }
    bool mul_cmd = Interpreter::get_instance().register_command(3, mul_creator(it, end));

    Command* div_creator(std::string::iterator & it, std::string::iterator & end){
        return new Div();
    }
    bool div_cmd = Interpreter::get_instance().register_command(4, div_creator(it, end));

    Command* mod_creator(std::string::iterator & it, std::string::iterator & end){
        return new Mod();
    }
    bool mod_cmd = Interpreter::get_instance().register_command(5, mod_creator(it, end));
};