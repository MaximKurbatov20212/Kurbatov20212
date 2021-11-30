#ifndef COMMAND
#define COMMAND
#include"my_stack.hpp"

class Command{
public:
    virtual void apply(MyStack& _stk) {};
    
    virtual void apply() {};

    virtual void print(std::string::iterator& it, std::string::iterator& end) {};

    // Throws exception "too few elements", if stack size < i
    bool check(MyStack& _stk, size_t i){
        if(_stk.size() < i){
            Interpreter_error("too few elements");
            return true;
        }
        return false;
    }
};

class Add: public Command{
    // Adds the top two numbers on the stack and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        if(check(_stk , 2)) {return;}
        int right = _stk.pop();
        int left = _stk.pop();
        _stk.push(left + right);
    }
};

class Sub: public Command{
    // Subtracts the top number from the second and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        if(check(_stk, 2)) {return;}
        int right = _stk.pop();
        int left = _stk.pop();
        _stk.push(left - right);
    }
};

class Mul: public Command{
    // Multiplies the top two numbers on the stack and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        if(check(_stk, 2)) {return;}
        int right = _stk.pop();
        int left = _stk.pop();
        _stk.push(left * right);
    }
};

class Div: public Command{
    // Divides the top number from the second and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        if(check(_stk, 2)) {return;}
        int right = _stk.pop();
        if(_stk.top() == 0) {
             _stk.push(right);
            throw Interpreter_error("division by zero");
        }
        int left = _stk.pop();
        _stk.push(left / right);
    }
};

class Mod: public Command{
    // Takes the remainder of the division of the second number from the top and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        if(check(_stk, 2)) {return;}
        int right = _stk.pop();
        int left = _stk.pop();
        _stk.push(left % right);
    }
};

class Dup: public Command{
    // Copies the top of the stack and pushes it onto the stack
    // Throws exception "too few elements", if stack size < 1
    void apply(MyStack& _stk) override{
        if (check(_stk, 1)) {return;}
        _stk.push(_stk.top());
    }
};

class Drop: public Command{
    // Deletes top number
    // Throws exception "too few elements", if stack size < 1
    void apply(MyStack& _stk) override{
        if (check(_stk, 1)) {return;}
        _stk.pop();
    }
};

class Point: public Command{
    // Deletes top number and prints it
    // Throws exception "too few elements", if stack size < 1
    void apply(MyStack& _stk) override{
        if (check(_stk, 1)) {return;}
        std::cout << _stk.pop() << std::endl;
    }
};

class Swap: public Command{
    // Swaps the top two numbers on the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        if(check(_stk, 2)) {return;}
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push(top_1);
        _stk.push(top_2);
    }
};

class Rot: public Command{
    // Loops the top three numbers on the stack
    // Throws exception "too few elements", if stack size < 3
    void apply(MyStack& _stk) override{
        if (check(_stk, 3)) {return;}
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        int top_3 = _stk.pop();
        _stk.push(top_1);
        _stk.push(top_3);
        _stk.push(top_2);
    }
};

class Over: public Command{
    // Copies the second number and pushes a copy over the top one.
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        if(check(_stk, 2)) {return;}
        int top_1 = _stk.pop();
        int top_2 = _stk.top();
        _stk.push(top_1);
        _stk.push(top_2);
    }
};

class Emit: public Command{
    // Prints the top number on the stack as ascii code and pop of the stack.
    // Throws exception "too few elements", if stack size < 1
    void apply(MyStack& _stk) override{
         if (check(_stk, 1)) {return;}
        int top = _stk.pop();
        if(std::isprint(top)) {
            std::cout << char(top); 
        }
    }
};

class Cr: public Command{ //???
    // Does line break
    void apply(MyStack& _stk) override{
        std::cout << std::endl;        
    }
};

class Greater: public Command{ 
    // Returns true if the second number is greater than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        if (check(_stk, 2)) {return;}
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push((int)(top_2 > top_1));
    }
};

class Less: public Command{ 
    // Returns true if the second number is less than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        if (check(_stk, 2)) {return;}
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push((int)(top_2 < top_1));   
    }
};

class Equal: public Command{ 
    // Returns true if the second number is equal than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        if (check(_stk, 2)) {return;}
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push((int)(top_1 == top_2));   
    }
};

class Print: public Command{ 
    // Prints all between ." "
    void print(std::string::iterator& it, std::string::iterator& end) override{
        while(it != end){
            std::cout << (*it);
            it++;
            if((*it) == '"'){
                it++;
                break;
            }
        }
        std::cout << std::endl;
    }
};
#endif