#ifndef MYSTACK
#define MYSTACK
#include <iostream>
#include <stack>
#include "interpreter_error.hpp"
class MyStack{
public:
    // Returns the top number on the stack and deletes it
    int pop(){
        if (stk.size() == 0) {throw (Interpreter_error("no elements\n"));}
        int a = stk.top();
        stk.pop();
        return a;
    }

    // Returns the top number on the stack
    int top(){return stk.top();}

    // Puts a number on the top of the stack
    void push(int a){ stk.push(a);}

    // Returns size of stack
    size_t size() const {return stk.size();}

    // Prints stack
    friend std::ostream& operator<<(std::ostream &out, const MyStack& a);
    
    void clear(){
        while(stk.size() > 0) {stk.pop();}
    }
private:
    std::stack<int> stk;     
};

#endif