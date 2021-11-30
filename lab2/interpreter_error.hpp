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

#endif