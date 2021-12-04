#ifndef COMMAND
#define COMMAND
#include"my_stack.hpp"
#include "interpreter.hpp"
#include <string>
#include <sstream>


class Command{
public:
    virtual void apply(Context& context) = 0;
};


// std::function
// Add extends BinOp
// Add::op -> std::function<int(int, int)>
// std::divides, std::multiplies

// BinCommand::apply(Context & context)
// virtual BinCommand:op -> std::function<int(int, int)>
// stack = context.stack
// n1 = stack.pop();
// n2 = stack.pop();
// stack.push(this.op()(n1, n2))

class Add: public Command{
    // Adds the top two numbers on the stack and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    // Throws exception "out of range of int", if a + b is not int
    void apply(Context& context) override{
        int right = context.stk.pop(2);
        int left = context.stk.pop();
        context.stk.push(left + right);
    }
};

class Sub: public Command{
    // Subtracts the top number from the second and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    // Throws exception "out of range of int", if a - b is not int
    void apply(Context& context) override{
        int right = context.stk.pop();
        int left = context.stk.pop();
        context.stk.push(left - right);
    }
};

class Mul: public Command{
    // Multiplies the top two numbers on the stack and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    // Throws exception "out of range of int", if a * b is not int
    void apply(Context& context) override{
        int right = context.stk.pop();
        int left = context.stk.pop();
        context.stk.push(left * right);
    }
};

class Div: public Command{
    // Divides the top number from the second and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context& context) override{
        if(context.stk.top() == 0) {throw Interpreter_error("division by zero\n");}
        int right = context.stk.pop();
        int left = context.stk.pop();
        context.stk.push(left / right);
    }
};

class Mod: public Command{
    // Takes the remainder of the division of the second number from the top and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context& context) override{
        if(context.stk.top() == 0) {throw Interpreter_error("division by zero\n");}
        int right = context.stk.pop();
        int left = context.stk.pop();
        context.stk.push(left % right);
    }
};

class Dup: public Command{
    // Copies the top of the stack and pushes it onto the stack
    // Throws exception "too few elements", if stack size < 1
    void apply(Context& context) override{
        context.stk.push(context.stk.top());
    }
};

class Drop: public Command{
    // Deletes top number
    // Throws exception "too few elements", if stack size < 1
    void apply(Context& context) override{
        context.stk.pop();
    }
};

class Point: public Command{
    // Deletes top number and prints it
    // Throws exception "too few elements", if stack size < 1
    void apply(Context& context) override{
        std::string str;
        int a = context.stk.pop();
        result << a;
//        if (a < 0){result.append("-");}
//        get_str(abs(a), result);
    }
};

class Swap: public Command{
    // Swaps the top two numbers on the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context& context) override{
        int top_1 = context.stk.pop();
        int top_2 = context.stk.pop();
        context.stk.push(top_1);
        context.stk.push(top_2);
    }
};

class Rot: public Command{
    // Loops the top three numbers on the stack
    // Throws exception "too few elements", if stack size < 3
    void apply(Context& context) override{
        int top_1 = context.stk.pop();
        int top_2 = context.stk.pop();
        int top_3 = context.stk.pop();
        context.stk.push(top_1);
        context.stk.push(top_3);
        context.stk.push(top_2);
    }
};

class Over: public Command{
    // Copies the second number and pushes a copy over the top one.
    // Throws exception "too few elements", if stack size < 2
    void apply(Context& context) override{
        int top_1 = context.stk.pop();
        int top_2 = context.stk.top();
        context.stk.push(top_1);
        context.stk.push(top_2);
    }
};

class Emit: public Command{
    // Prints the top number on the stack as ascii code and pop of the stack.
    // Throws exception "too few elements", if stack size < 1
    void apply(Context& context) override{
        int top = context.stk.pop();
        result+=char(top);
        result+='\n';
    }
};

class Cr: public Command{ //???
    // Does line break
    void apply(Context& context) override{
        result+='\n';
        // std::cout << std::endl;        
    }
};

class Greater: public Command{ 
    // Returns true if the second number is greater than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(Context& context) override{
        int top_1 = context.stk.pop();
        int top_2 = context.stk.pop();
        context.stk.push(top_2 > top_1);
    }
};

class Less: public Command{ 
    // Returns true if the second number is less than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(Context& context) override{
        int top_1 = context.stk.pop();
        int top_2 = context.stk.pop();
        context.stk.push(top_2 < top_1);
    }
};

class Equal: public Command{ 
    // Returns true if the second number is equal than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(Context& context) override{
        int top_1 = context.stk.pop();
        int top_2 = context.stk.pop();
        context.stk.push((int)(top_1 == top_2));   
    }
};

class Print: public Command{ 
    // Prints all between ." "
    void apply(Context& context) override{
        std::stringstream str;
        while (context.it != context.end && context.it != '"') {
            str << context.it;
            it++;
        }
        if (context.it == context.end) throw Interpreter_error("closing bracket is missing");
        it++;
        result << str;
    }
    
};
#endif