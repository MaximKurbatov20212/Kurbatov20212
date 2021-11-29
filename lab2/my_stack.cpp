#include "my_stack.hpp"

std::ostream& operator<<(std::ostream &out, const MyStack& a){
    MyStack b = a;
    size_t s_stk = a.size();
    if(s_stk == 0) {out << "stack is empty" << std::endl;}
    out << s_stk << std::endl;
    for(int i = s_stk - 1 ; i >= 0 ; --i){
        out << "                |" << b.pop() << '|' << std::endl;
    }
    
} 