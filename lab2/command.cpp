#include <iostream>
#include "command.hpp"
#include "interpreter.hpp"

namespace{
    Command* add_creator(){
        return new Add();
    } 
    bool add_cmd = Interpreter::get_instance().register_command(1, add_creator);

    Command* sub_creator(){
        return new Sub();
    }
    bool sub_cmd = Interpreter::get_instance().register_command(2, sub_creator);

    Command* mul_creator(){
        return new Mul();
    }
    bool mul_cmd = Interpreter::get_instance().register_command(3, mul_creator);

    Command* div_creator(){
        return new Div();
    }
    bool div_cmd = Interpreter::get_instance().register_command(4, div_creator);

    Command* mod_creator(){
        return new Mod();
    }
    bool mod_cmd = Interpreter::get_instance().register_command(5, mod_creator);

    Command* dup_creator(){
        return new Dup();
    }
    bool dup_cmd = Interpreter::get_instance().register_command(6, dup_creator);

    Command* drop_creator(){
        return new Drop();
    }
    bool drop_cmd = Interpreter::get_instance().register_command(7, drop_creator);

    Command* point_creator(){
        return new Point();
    }
    bool point_cmd = Interpreter::get_instance().register_command(8, point_creator);

    Command* swap_creator(){
        return new Swap();
    }
    bool swap_cmd = Interpreter::get_instance().register_command(9, swap_creator);

    Command* rot_creator(){
        return new Rot();
    }
    bool rot_cmd = Interpreter::get_instance().register_command(10, rot_creator);

    Command* over_creator(){
        return new Over();
    }
    bool over_cmd = Interpreter::get_instance().register_command(11, over_creator);

    Command* emit_creator(){
        return new Emit();
    }
    bool emit_cmd = Interpreter::get_instance().register_command(12, emit_creator);

    Command* cr_creator(){
        return new Cr();
    }
    bool cr_cmd = Interpreter::get_instance().register_command(13, cr_creator);

    Command* greater_creator(){
        return new Greater();
    }
    bool greater_cmd = Interpreter::get_instance().register_command(14, greater_creator);

    Command* less_creator(){
        return new Less();
    }
    bool less_cmd = Interpreter::get_instance().register_command(15, less_creator);

    Command* equal_creator(){
        return new Equal();
    }
    bool equal_cmd = Interpreter::get_instance().register_command(16, equal_creator);

    Command* print_creator(){
        return new Print();
    }
    bool print_cmd = Interpreter::get_instance().register_command(17, print_creator);
}