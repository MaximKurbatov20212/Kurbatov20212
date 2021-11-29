#ifndef COMMAND
#define COMMAND
#include"interpreter.hpp"
#include"my_stack.hpp"

class Command{
public:
    virtual void apply(MyStack& _stk) = 0;
};

class Add: public Command{
    void apply(MyStack& _stk) override{
        std::cout << &_stk << std::endl;
        int left = _stk.pop();
        int right = _stk.pop();
        _stk.push(left + right);
    }
};

class Sub: public Command{
    void apply(MyStack& _stk) override{
        std::cout << &_stk << std::endl;
        int left = _stk.pop();
        int right = _stk.pop();
        _stk.push(right - left);
    }
};

class Mul: public Command{
    void apply(MyStack& _stk) override{
        int left = _stk.pop();
        int right = _stk.pop();
        _stk.push(left * right);
    }
};

class Div: public Command{
    void apply(MyStack& _stk) override{
        int left = _stk.pop();
        int right = _stk.pop();
        if(left == 0) throw(std::runtime_error("division by zero"));
        _stk.push(left / right);
    }
};

class Mod: public Command{
    void apply(MyStack& _stk) override{
        int left = _stk.pop();
        int right = _stk.pop();
        _stk.push(left % right);
    }
};
#endif