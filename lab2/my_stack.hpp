#ifndef MYSTACK
#define MYSTACK

#include <iostream>
#include <stack>
#include "interpreter_error.hpp"

class MyStack {
public:
    // Returns the top number on the stack and deletes it
    int pop() {
        if (stk.empty()) throw interpreter_error("too few elements\n");
        int a = stk.top();
        stk.pop();
        return a;
    }

    // Returns the top number on the stack
    int top() {
        if (stk.empty()) throw interpreter_error("too few elements\n");
        return stk.top();
    }

    // Puts a number on the top of the stack
    void push(int a) { stk.push(a); }

    // Returns size of stack
    int size() const { return stk.size(); }

    // Prints stack
    friend std::ostream &operator<<(std::ostream &out, const MyStack &a);

    // Deleted all elements
    void clear() {
        stk = std::stack<int>();
    }

private:
    std::stack<int> stk;
};

#endif