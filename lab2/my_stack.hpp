#ifndef MYSTACK
#define MYSTACK
#include<stack>
class MyStack{
public:
    static MyStack& get_stack(){
        static MyStack my_stack;
        return my_stack;
    }    

    int pop(){
        if (stk.size() == 0) {throw (std::runtime_error("no elements"));}
        int a = stk.top();
        stk.pop();
        return a;
    }

    void push(int a){stk.push(a);}

    size_t size(){return stk.size();}
private:
    std::stack<int> stk;     
};

#endif