#ifndef COMMAND
#define COMMAND

class Command{
public:
    virtual void apply() = 0;    
};

class Add: public Command{
    void apply() override{
        int left = Interpreter::stk.top();
        Interpreter::stk.pop();
        int right = Interpreter::stk.top();
        Interpreter::stk.pop();
        Interpreter::stk.push(left + right);
    }
};

class Sub: public Command{
        void apply() override{
        int left = Interpreter::stk.top();
        Interpreter::stk.pop();
        int right = Interpreter::stk.top();
        Interpreter::stk.pop();
        Interpreter::stk.push(right - left);
    }
};

class Mul: public Command{
       void apply() override{
        int left = Interpreter::stk.top();
        Interpreter::stk.pop();
        int right = Interpreter::stk.top();
        Interpreter::stk.pop();
        Interpreter::stk.push(left * right);
    }
};

class Div: public Command{
        void apply() override{
        int left = Interpreter::stk.top();
        Interpreter::stk.pop();
        int right = Interpreter::stk.top();
        Interpreter::stk.pop();
        if(left == 0) throw(std::runtime_error("division by zero"));
        Interpreter::stk.push(left / right);
    }
};

class Mod: public Command{
        void apply() override{
        int left = Interpreter::stk.top();
        Interpreter::stk.pop();
        int right = Interpreter::stk.top();
        Interpreter::stk.pop();
        Interpreter::stk.push(left % right);
    }
};



#endif