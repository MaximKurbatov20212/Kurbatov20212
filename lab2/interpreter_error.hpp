#ifndef INTERPRETER_ERROR
#define INTERPRETER_ERROR
#include <stdexcept>

class Interpreter_error: public std::runtime_error{
public:
    // Throws matching exception
    Interpreter_error(std::string msg): std::runtime_error(msg){};
};
#endif