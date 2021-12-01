#ifndef COMMAND
#define COMMAND
#include"my_stack.hpp"
#include <cstring>
#include <cmath>
#include <climits>

class Command{
public:
    virtual void apply(MyStack& _stk) {};
    
    virtual void apply(std::string& result) {} ;

    virtual void apply(MyStack& _stk, std::string& result) {};

    virtual void print(std::string::iterator& it, std::string::iterator& end, std::string& result) {};

    // Throws exception "too few elements", if stack size < i
    void check(MyStack& _stk, size_t i){
        if(_stk.size() < i){
            throw Interpreter_error("too few elements\n");
        }
    }
    // Converts from int to string
    void get_str(int a, std::string& str){ 
        int b = a % 10;
        a = a / 10;
        while(a > 0){
            b = b * 10 + a % 10;    
            a = a / 10;
        }
        while(b > 0){
            str+= (b % 10) + '0';
            b = b / 10;
        }
        //str+='\n';
    }

    bool is_overflow(long long& res){
        if (res > INT32_MAX || res < -INT32_MAX ) {return true;}
        return false;
    }
};

class Add: public Command{
    // Adds the top two numbers on the stack and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    // Throws exception "out of range of int", if a + b is not int
    void apply(MyStack& _stk) override{
        check(_stk , 2);
        int right = _stk.pop();
        int left = _stk.pop();
        long long res = right + left;
        if(is_overflow(res)) throw Interpreter_error("out of range of int\n");
        _stk.push(left + right);
    }
};

class Sub: public Command{
    // Subtracts the top number from the second and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    // Throws exception "out of range of int", if a - b is not int
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int right = _stk.pop();
        int left = _stk.pop();
        long long res = left - right;
        if(is_overflow(res)) throw Interpreter_error("out of range of int\n");
        _stk.push(res);
    }
};

class Mul: public Command{
    // Multiplies the top two numbers on the stack and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    // Throws exception "out of range of int", if a * b is not int
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int right = _stk.pop();
        int left = _stk.pop();
        long long res = left * right;
        //std::cerr << res;
        if(is_overflow(res)) throw Interpreter_error("out of range of int\n");
        _stk.push(res);
    }
};

class Div: public Command{
    // Divides the top number from the second and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        if(_stk.top() == 0) {throw Interpreter_error("division by zero\n");}
        int right = _stk.pop();
        int left = _stk.pop();
        _stk.push(left / right);
    }
};

class Mod: public Command{
    // Takes the remainder of the division of the second number from the top and pushes the result onto the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        if(_stk.top() == 0) {throw Interpreter_error("division by zero\n");}
        int right = _stk.pop();
        int left = _stk.pop();
        _stk.push(left % right);
    }
};

class Dup: public Command{
    // Copies the top of the stack and pushes it onto the stack
    // Throws exception "too few elements", if stack size < 1
    void apply(MyStack& _stk) override{
        check(_stk, 1);
        _stk.push(_stk.top());
    }
};

class Drop: public Command{
    // Deletes top number
    // Throws exception "too few elements", if stack size < 1
    void apply(MyStack& _stk) override{
        check(_stk, 1);
        _stk.pop();
    }
};

class Point: public Command{
    // Deletes top number and prints it
    // Throws exception "too few elements", if stack size < 1
    void apply(MyStack& _stk, std::string& result) override{
        check(_stk, 1);
        std::string str;
        int a = _stk.pop();
        if (a < 0){result.append("-");}
        get_str(abs(a), result);
    }
};

class Swap: public Command{
    // Swaps the top two numbers on the stack
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        check(_stk, 2);
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
    // Copies the second number and pushes a copy over the top one.
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int top_1 = _stk.pop();
        int top_2 = _stk.top();
        _stk.push(top_1);
        _stk.push(top_2);
    }
};

class Emit: public Command{
    // Prints the top number on the stack as ascii code and pop of the stack.
    // Throws exception "too few elements", if stack size < 1
    void apply(MyStack& _stk, std::string& result) override{
        check(_stk, 1);
        int top = _stk.pop();
        result+=(char)(top);
        result+='\n';
    }
};

class Cr: public Command{ //???
    // Does line break
    void apply(std::string& result) override{
        result+='\n';
        // std::cout << std::endl;        
    }
};

class Greater: public Command{ 
    // Returns true if the second number is greater than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push((int)(top_2 > top_1));
    }
};

class Less: public Command{ 
    // Returns true if the second number is less than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push((int)(top_2 < top_1));   
    }
};

class Equal: public Command{ 
    // Returns true if the second number is equal than the top 
    // Throws exception "too few elements", if stack size < 2
    void apply(MyStack& _stk) override{
        check(_stk, 2);
        int top_1 = _stk.pop();
        int top_2 = _stk.pop();
        _stk.push((int)(top_1 == top_2));   
    }
};

class Print: public Command{ 
    // Prints all between ." "
    void print(std::string::iterator& it, std::string::iterator& end, std::string& result) override{
        std::string::iterator it_1 = it;
        std::string::iterator end_1 = end;
        do{
            if(it_1 == end_1){throw Interpreter_error("there is no second \"\n");}
            it_1++;
        }while((*it_1) != '"');

        while(it != end){
            result+=(*it);
            it++;
            if((*it) == '"'){
                it++;
                result+=('\n');
                //std::cout << std::endl;  
                return;
            }
        }
    }
    
};
#endif