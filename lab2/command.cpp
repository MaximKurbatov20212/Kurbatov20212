#include <iostream>
#include "command.hpp"
#include "interpreter.hpp"

namespace{
    Command* add_creator(std::string::iterator & it, std::string::iterator & end){
        return new Add();
    } 
    bool add_cmd = Interpreter::get_instance().register_command(1, add_creator);

    Command* sub_creator(std::string::iterator & it, std::string::iterator & end){
        return new Sub();
    }
    bool sub_cmd = Interpreter::get_instance().register_command(2, sub_creator);

    Command* mul_creator(std::string::iterator & it, std::string::iterator & end){
        return new Mul();
    }
    bool mul_cmd = Interpreter::get_instance().register_command(3, mul_creator);

    Command* div_creator(std::string::iterator & it, std::string::iterator & end){
        return new Div();
    }
    bool div_cmd = Interpreter::get_instance().register_command(4, div_creator);

    Command* mod_creator(std::string::iterator & it, std::string::iterator & end){
        return new Mod();
    }
    bool mod_cmd = Interpreter::get_instance().register_command(5, mod_creator);

    Command* dup_creator(std::string::iterator & it, std::string::iterator & end){
        return new Dup();
    }
    bool dup_cmd = Interpreter::get_instance().register_command(6, dup_creator);

    Command* drop_creator(std::string::iterator & it, std::string::iterator & end){
        return new Drop();
    }
    bool drop_cmd = Interpreter::get_instance().register_command(7, drop_creator);

    Command* point_creator(std::string::iterator & it, std::string::iterator & end){
        return new Point();
    }
    bool point_cmd = Interpreter::get_instance().register_command(8, point_creator);

    Command* swap_creator(std::string::iterator & it, std::string::iterator & end){
        return new Swap();
    }
    bool swap_cmd = Interpreter::get_instance().register_command(9, swap_creator);

    Command* rot_creator(std::string::iterator & it, std::string::iterator & end){
        return new Rot();
    }
    bool rot_cmd = Interpreter::get_instance().register_command(10, rot_creator);

    Command* over_creator(std::string::iterator & it, std::string::iterator & end){
        return new Over();
    }
    bool over_cmd = Interpreter::get_instance().register_command(11, over_creator);

    Command* emit_creator(std::string::iterator & it, std::string::iterator & end){
        return new Emit();
    }
    bool emit_cmd = Interpreter::get_instance().register_command(12, emit_creator);

    Command* cr_creator(std::string::iterator & it, std::string::iterator & end){
        return new Cr();
    }
    bool cr_cmd = Interpreter::get_instance().register_command(13, cr_creator);

    Command* above_creator(std::string::iterator & it, std::string::iterator & end){
        return new Above();
    }
    bool above_cmd = Interpreter::get_instance().register_command(14, above_creator);

    Command* below_creator(std::string::iterator & it, std::string::iterator & end){
        return new Below();
    }
    bool below_cmd = Interpreter::get_instance().register_command(15, below_creator);

    Command* equal_creator(std::string::iterator & it, std::string::iterator & end){
        return new Equal();
    }
    bool equal_cmd = Interpreter::get_instance().register_command(16, equal_creator);



};