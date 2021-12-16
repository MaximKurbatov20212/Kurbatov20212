#ifndef INTERPRETER_ERROR
#define INTERPRETER_ERROR
#include <stdexcept>

// CR: either call it InterpreterError or interpreter_error (I prefer the latter since it's how exceptions usually called)
class Interpreter_error: public std::runtime_error{
public:
    // Throws matching exception
    explicit Interpreter_error(const std::string& msg): std::runtime_error(msg){};
};
#endif