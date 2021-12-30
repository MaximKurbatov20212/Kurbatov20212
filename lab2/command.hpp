#ifndef COMMAND
#define COMMAND

#include "my_stack.hpp"
#include <string>
#include <sstream>

struct Context {
    Context(MyStack &stk, std::string::iterator &it, std::string::iterator &end) : stk(stk), it(it), end(end) {}

    MyStack &stk;
    std::string::iterator &it;
    std::string::iterator &end;
    std::stringstream sstr;
    std::string str;
};

class Command {
public:
    virtual void apply(Context &context) = 0;
};

class Add : public Command {
    // Adds the top two numbers on the stack and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw interpreter_error("too few elements");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second + first);
    }
};

class Sub : public Command {
    // Subtracts the top number from the second and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw interpreter_error("too few elements");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second - first);
    }
};

class Mul : public Command {
    // Multiplies the top two numbers on the stack and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw interpreter_error("too few elements");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second * first);
    }
};

class Div : public Command {
    // Divides the top number from the second and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw interpreter_error("too few elements");
        if (context.stk.top() == 0) throw interpreter_error("division by zero");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second / first);
    }
};

class Mod : public Command {
    // Takes the remainder of the division of the second number from the top and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw interpreter_error("too few elements");
        if (context.stk.top() == 0) throw interpreter_error("division by zero");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second % first);
    }
};

class Dup : public Command {
    // Copies the top of the stack and pushes it onto the stack
    // Throws exception "too few elements", if stack size < 1
    void apply(Context &context) override {
        context.stk.push(context.stk.top());
    }
};

class Drop : public Command {
    // Deletes top number
    // Throws exception "too few elements", if stack size < 1
    void apply(Context &context) override {
        context.stk.pop();
    }
};

class Point : public Command {
    // Deletes top number and prints it
    // Throws exception "too few elements", if stack size < 1
    void apply(Context &context) override {
        std::string str;
        int a = context.stk.pop();
        context.sstr << a;
        context.sstr << ' ';
    }
};

class Swap : public Command {
    // Swaps the top two numbers on the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw interpreter_error("too few elements");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(first);
        context.stk.push(second);
    }
};

class Rot : public Command {
    // Loops the top three numbers on the stack
    // Throws exception "too few elements", if stack size < 3
    void apply(Context &context) override {
        if (context.stk.size() < 3) throw interpreter_error("too few elements");
        int first = context.stk.pop();
        int second = context.stk.pop();
        int third = context.stk.pop();
        context.stk.push(first);
        context.stk.push(third);
        context.stk.push(second);
    }
};

class Over : public Command {
    // Copies the second number and pushes a copy over the top one.
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw interpreter_error("too few elements");
        int first = context.stk.pop();
        int second = context.stk.top();
        context.stk.push(first);
        context.stk.push(second);
    }
};

class Emit : public Command {
    // Prints the top number on the stack as ascii code and pop of the stack.
    // Throws exception "too few elements", if stack size < 1
    void apply(Context &context) override {
        int top = context.stk.pop();
        if (top < 0 || top > 128) throw interpreter_error("number on stack is out of ASCII range and cannot be displayed");
        context.sstr << char(top);
        context.sstr << '\n';
    }
};

class Cr : public Command {
    // Does line break
    void apply(Context &context) override {
        context.sstr << '\n';
    }
};

class Greater : public Command {
    // Returns true if the second number is greater than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw interpreter_error("too few elements");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second > first);
    }
};

class Less : public Command {
    // Returns true if the second number is less than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw interpreter_error("too few elements");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second < first);
    }
};

class Equal : public Command {
    // Returns true if the second number is equal than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw interpreter_error("too few elements");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(first == second);
    }
};

class Print : public Command {
    // Prints all between ." "
    void apply(Context &context) override {
        if(context.it == context.end) throw interpreter_error("closing bracket is missing");
        bool escape = false; // was there previously '\' or not
        std::string res;
        while(context.it != context.end){
            if(*(context.it) == '"'){
                context.it++;
                if(escape == false) {
                    context.sstr << res << '\n';
                    return;
                }
                res += (*(context.it - 1));  
                escape = false;  
            }
            else if(*(context.it) == '\\'){
                context.it++;
                if(escape == false){
                    escape = true;
                    continue;
                }
                res += (*(context.it - 1));
                escape = false;
            }
            else{
                if(escape == true){
                    std::string a = "can't escape ";
                    a += (*(context.it));
                    throw interpreter_error(a);
                } 
                res += (*(context.it));
                context.it++;
            }
        }
        throw interpreter_error("closing bracket is missing");
    }
};

#endif