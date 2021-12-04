#include <iostream>
#include "command.hpp"
#include "interpreter.hpp"

namespace{
    bool add_cmd = Interpreter::get_instance().register_command("add", new Add);

    bool sub_cmd = Interpreter::get_instance().register_command("sub", new Sub);
    
    bool mul_cmd = Interpreter::get_instance().register_command("mul", new Mul);
    
    bool div_cmd = Interpreter::get_instance().register_command("div", new Div);
    
    bool mod_cmd = Interpreter::get_instance().register_command("mod", new Mod);
    
    bool dup_cmd = Interpreter::get_instance().register_command("dup", new Dup);
    
    bool drop_cmd = Interpreter::get_instance().register_command("drop", new Drop);
    
    bool point_cmd = Interpreter::get_instance().register_command(".", new Point);
    
    bool swap_cmd = Interpreter::get_instance().register_command("swap", new Swap);
    
    bool rot_cmd = Interpreter::get_instance().register_command("rot", new Rot);
    
    bool over_cmd = Interpreter::get_instance().register_command("over", new Over);
    
    bool emit_cmd = Interpreter::get_instance().register_command("emit", new Emit);
    
    bool cr_cmd = Interpreter::get_instance().register_command("cr", new Cr);
    
    bool greater_cmd = Interpreter::get_instance().register_command(">", new Greater);
    
    bool less_cmd = Interpreter::get_instance().register_command("<", new Less);
    
    bool equal_cmd = Interpreter::get_instance().register_command("=", new Equal);

    bool print_cmd = Interpreter::get_instance().register_command(".\"", new Print);
}