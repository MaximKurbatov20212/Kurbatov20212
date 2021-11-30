#ifndef INTERPRETER_ERROR
#define INTERPRETER_ERROR
#include <stdexcept>

class Interpreter_error: public std::runtime_error{
public:
    // Throws matching exception
    // "too much number" if number is not in the range of int    
    // "unkown symbol" if you entered an incorrect command
    // "division by zero" 
    Interpreter_error(std::string msg): std::runtime_error(msg){};
};
/*
class too_much_number:  public Interpreter_error{
public:    
    too_much_number(std::string msg): Interpreter_error("too much number"){};
};

class unknown_symbol:  public Interpreter_error{
public:    
    unknown_symbol(std::string msg): Interpreter_error("unknown symbol"){};
};

class division_by_zero:  public Interpreter_error{
public:    
    division_by_zero(std::string msg): Interpreter_error("division by zero"){};
};

class out_of_range_of_int:  public Interpreter_error{
public:    
    out_of_range_of_int(std::string msg): Interpreter_error("out of range of int"){};
};
*/

#endif