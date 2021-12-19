#ifndef INTERPRETER_ERROR
#define INTERPRETER_ERROR
#include <stdexcept>

class interpreter_error: public std::runtime_error{
public:
    // Throws matching exception
    explicit interpreter_error(const std::string& msg): std::runtime_error(msg){};
};
#endif