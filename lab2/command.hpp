#ifndef COMMAND
#define COMMAND
#include "interpreter.hpp"
#include<stack>

class Command{
public:
    Interpreter interpreter = Interpreter::get_instance();
    virtual void apply() = 0;    
};

class Add: public Command{
    void apply() override{
        int left = interpreter.stk.top();
        interpreter.stk.pop();
        int right = interpreter.stk.top();
        interpreter.stk.pop();
        interpreter.stk.push(left + right);
    }
};

class Sub: public Command{
        void apply() override{
        int left = interpreter.stk.top();
        interpreter.stk.pop();
        int right = interpreter.stk.top();
        interpreter.stk.pop();
        interpreter.stk.push(right - left);
    }
};

class Mul: public Command{
       void apply() override{
        int left = interpreter.stk.top();
        interpreter.stk.pop();
        int right = interpreter.stk.top();
        interpreter.stk.pop();
        interpreter.stk.push(left * right);
    }
};

class Div: public Command{
        void apply() override{
        int left = interpreter.stk.top();
        interpreter.stk.pop();
        int right = interpreter.stk.top();
        interpreter.stk.pop();
        if(left == 0) throw(std::runtime_error("division by zero"));
        interpreter.stk.push(left / right);
    }
};

class Mod: public Command{
        void apply() override{
        int left = interpreter.stk.top();
        interpreter.stk.pop();
        int right = interpreter.stk.top();
        interpreter.stk.pop();
        interpreter.stk.push(left % right);
    }
};



#endif