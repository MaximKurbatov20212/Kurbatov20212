#ifndef COMMAND
#define COMMAND
#include"my_stack.hpp"

class Command{
public:
    virtual void apply(MyStack& _stk) = 0;
    void check(MyStack& _stk, size_t i){
        if(_stk.size() < i){
            Interpreter_error("too few elements");
        }
        return;
    }
};

class Add: public Command{
    void apply(MyStack& _stk) override{
        check(_stk , 2);
        int right = _stk.pop();
        int left = _stk.pop();
        _stk.push(left + right);
    }
};

class Sub: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int right = _stk.pop();
        int left = _stk.pop();
        _stk.push(left - right);
    }
};

class Mul: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int right = _stk.pop();
        int left = _stk.pop();
        _stk.push(left * right);
    }
};

class Div: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int right = _stk.pop();
        if(_stk.top() == 0) {
             _stk.push(right);
            throw(Interpreter_error("division by zero"));
        }
        int left = _stk.pop();
        _stk.push(left / right);
    }
};

class Mod: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int right = _stk.pop();
        int left = _stk.pop();
        _stk.push(left % right);
    }
};

class Dup: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 1);
        _stk.push(_stk.top());
    }
};

class Drop: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 1);
        _stk.pop();
    }
};

class Point: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 1);
        std::cout << _stk.pop() << std::endl;
    }
};

class Swap: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push(top_1);
        _stk.push(top_2);
    }
};

class Rot: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 3);
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        int top_3 = _stk.pop();
        _stk.push(top_1);
        _stk.push(top_3);
        _stk.push(top_2);
    }
};

class Over: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int top_1 = _stk.pop();
        int top_2 = _stk.top();
        _stk.push(top_1);
        _stk.push(top_2);
    }
};


class Emit: public Command{
    void apply(MyStack& _stk) override{
        check(_stk, 1);
        int top = _stk.pop();
        if(std::isprint(top)) {
            std::cout << char(top); 
        }
        
    }
};

class Cr: public Command{ //???
    void apply(MyStack& _stk) override{
        std::cout << std::endl;        
    }
};

class Above: public Command{ 
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push((int)(top_2 > top_1));
    }
};

class Below: public Command{ 
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push((int)(top_2 < top_1));   
    }
};

class Equal: public Command{ 
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push((int)(top_1 == top_2));   
    }
};

#endif