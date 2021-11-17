#ifndef INTERPRETER_ERROR
#define INTERPRETER_ERROR

class Interpreter_error: public std::runtime_error{
public:
    Interpreter_error(std::string msg): std::runtime_error(msg){};
};

#endif