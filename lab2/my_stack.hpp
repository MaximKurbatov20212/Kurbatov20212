#ifndef MYSTACK
#define MYSTACK
#include <iostream>
#include <stack>
#include "interpreter_error.hpp"
class MyStack{
public:
    static MyStack& get_stack(){
        static MyStack my_stack;
        return my_stack;
    }    

    int pop(){
        if (stk.size() == 0) {throw (Interpreter_error("no elements"));}
        int a = stk.top();
        stk.pop();
        return a;
    }

    int top(){return stk.top();}

    void push(int a){ stk.push(a);}

    size_t size() const {return stk.size();}

    friend std::ostream& operator<<(std::ostream &out, const MyStack& a);
    
private:
    std::stack<int> stk;     
};

#endif