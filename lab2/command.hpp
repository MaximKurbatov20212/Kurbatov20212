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
        if (context.stk.size() < 2) throw Interpreter_error("too few elements\n");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second + first);
    }
};

class Sub : public Command {
    // Subtracts the top number from the second and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw Interpreter_error("too few elements\n");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second - first);
    }
};

class Mul : public Command {
    // Multiplies the top two numbers on the stack and pushes the result onto the stack
    // Throws exception "too few elements\n", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw Interpreter_error("too few elements\n");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second * first);
    }
};

class Div : public Command {
    // Divides the top number from the second and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw Interpreter_error("too few elements\n");
        if (context.stk.top() == 0) throw Interpreter_error("division by zero\n");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second / first);
    }
};

class Mod : public Command {
    // Takes the remainder of the division of the second number from the top and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw Interpreter_error("too few elements\n");
        if (context.stk.top() == 0) throw Interpreter_error("division by zero\n");
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
    }
};

class Swap : public Command {
    // Swaps the top two numbers on the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw Interpreter_error("too few elements\n");
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
        if (context.stk.size() < 3) throw Interpreter_error("too few elements\n");
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
        if (context.stk.size() < 2) throw Interpreter_error("too few elements\n");
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
        // CR: better error message. e.g. "Number on stack is out of ASCII range and cannot be displayed"
        // CR: also you do not have \n here at the end is it expected? I think it's better to remove \n everywhere
        // CR: and just add it when printing
        if (top < 0 || top > 128) throw Interpreter_error("is not printed");
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
        if (context.stk.size() < 2) throw Interpreter_error("too few elements\n");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second > first);
    }
};

class Less : public Command {
    // Returns true if the second number is less than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw Interpreter_error("too few elements\n");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(second < first);
    }
};

class Equal : public Command {
    // Returns true if the second number is equal than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(Context &context) override {
        if (context.stk.size() < 2) throw Interpreter_error("too few elements\n");
        int first = context.stk.pop();
        int second = context.stk.pop();
        context.stk.push(first == second);
    }
};

class Print : public Command {
    // Prints all between ." "
    // CR: rewrite using one of two approaches (parse until first " / support escaped quotes)
    void apply(Context &context) override {

        std::string::iterator last_bracket = context.end - 1;
        while (context.it != last_bracket) {
            if (*last_bracket == '\"')break;
            last_bracket--;
        }

        if (last_bracket == context.it + 1) {
            context.it = context.end;
            throw Interpreter_error("closing bracket is missing\n");
        }

        context.it += 2; // skip ."
        while (context.it != last_bracket) {
            context.sstr << *(context.it);
            context.it++;
        }
        context.it += 1; // skip "
        context.sstr << '\n';
    }
};

class Quit : public Command {
    // Force quit
    void apply(Context &context) override {
        context.sstr << "";
        // CR: please do not use exit in your code, it's really hard to track such exists (similar to goto)
        // CR: if you really want you can have some kind of flag is_exit in your context and set it here
        exit(EXIT_SUCCESS);
    }
};

#endif