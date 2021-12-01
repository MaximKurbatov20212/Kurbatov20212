#include <iostream>
#include <limits>
#include "interpreter.hpp"
#include "interpreter_error.hpp"
#include "command.hpp"
#include "my_stack.hpp"
#include <map>

bool Interpreter::is_digit(std::string::iterator& it, std::string::iterator& end){
    if(is_negative(it, end)) {return true;}
    // std::is_digit
    return (int)(*it) >= (int)'0' && (int)(*it) <= (int)'9';
}

long long Interpreter::get_num(std::string::iterator& it, std::string::iterator& end){
    // std::atoi
    long long res = 0;
    long long deg = 1;
    int k = 1;
    if((*it) == '-'){ 
        it++;
        k = -1;
    }
    do{
        if(is_digit(it,end)){
            res = res * deg + ((*it) - '0'); 
            //std::cout << "digit" << std::endl;
            deg = 10;
            
            if(res > INT32_MAX){  
                throw Interpreter_error("out of range of int\n");
            }
        }
        else if((*it) ==  ' '){
            it++;
            break;
        }
        else {
            throw Interpreter_error("no such command\n"); // Example: 123a
        }
        it++;
    }while(it != end);

    return res * k;
}

bool Interpreter::is_negative(std::string::iterator& it, std::string::iterator& end){
    if(it + 1 != end && it != end){
        std::string::iterator a = it + 1;
        if(*it == '-' && (int)(*a) >= (int)'0' && (int)(*a) <= (int)'9'){
            return true;
        }
    }
    return false;
}

bool Interpreter::is_cmd(std::string::iterator& it, std::string::iterator& end){
    if(is_negative(it, end)) {return false;}

    if((*it) == '+' || (*it) == '-' || (*it) == '*' || (*it) == '/' || (*it) == '.' || (*it) == '<'|| (*it) == '>'|| (*it) == '=') {return true;}

    if (it + 1 != end && (*it) == 'c' && *(it + 1) == 'r') {return true;}

    if ((it + 1 != end) && (it + 2 != end)){
        if ((*it) == 'm' && *(it + 1) == 'o' && *(it + 2) == 'd') {return true;}
        if ((*it) == 'd' && *(it + 1) == 'u' && *(it + 2) == 'p') {return true;}
        if ((*it) == 'r' && *(it + 1) == 'o' && *(it + 2) == 't') {return true;}
    }
    if ( (it + 1 != end) && (it + 2 != end) && (it + 3 != end)){
        if ((*it) == 'o' && *(it + 1) == 'v' && *(it + 2) == 'e' && *(it + 3) == 'r'){return true;}
        if ((*it) == 'd' && *(it + 1) == 'r' && *(it + 2) == 'o' && *(it + 3) == 'p'){return true;}
        if ((*it) == 'e' && *(it + 1) == 'm' && *(it + 2) == 'i' && *(it + 3) == 't'){return true;}
        if ((*it) == 's' && *(it + 1) == 'w' && *(it + 2) == 'a' && *(it + 3) == 'p'){return true;}
    }
    return false;
}

long long Interpreter::get_command(std::string::iterator& it, std::string::iterator& end){
    long a = INT32_MAX;
    if ((*it) == '+') {it++; return a + 1;}
    if ((*it) == '-') {it++; return a + 2;}
    if ((*it) == '*') {it++; return a + 3;}
    if ((*it) == '/') {it++; return a + 4;}
    if ((*it) == '>') {it++; return a + 14;}
    if ((*it) == '<') {it++; return a + 15;}
    if ((*it) == '=') {it++; return a + 16;}

    if((it + 1 != end) && (*it == '.') && (*(it + 1) == '"')){
        it += 2;
        return a + 17;
    }

    if ((*it) == '.') {it++; return a + 8;}

    if(it + 1 != end && (*it) == 'c' && *(it + 1) == 'r'){ //cr
        it += 2;
        return a + 13;
    }

    if ((it + 1 != end) && (it + 2 != end)){
        if ((*it) == 'm' && *(it + 1) == 'o' && *(it + 2) == 'd') { //mod
            it += 3;
            return a + 5;
        }
        if ((*it) == 'd' && *(it + 1) == 'u' && *(it + 2) == 'p') { //dup
            it += 3;
            return a + 6;
        }

        if ((*it) == 'r' && *(it + 1) == 'o' && *(it + 2) == 't') { //rot
            it += 3;
            return a + 10;
        }
    }   

    if ( (it + 1 != end) && (it + 2 != end) && (it + 3 != end)){
        if ((*it) == 'o' && *(it + 1) == 'v' && *(it + 2) == 'e' && *(it + 3) == 'r') { //over
            it += 4;
            return a + 11;
        }

        if ((*it) == 'd' && *(it + 1) == 'r' && *(it + 2) == 'o' && *(it + 3) == 'p') { //drop
            it += 4;
            return a + 7;
        }

        if ((*it) == 'e' && *(it + 1) == 'm' && *(it + 2) == 'i' && *(it + 3) == 't') { //emit
            it += 4;
            return a + 12;
        }

        if ((*it) == 's' && *(it + 1) == 'w' && *(it + 2) == 'a' && *(it + 3) == 'p') { //swap
            it += 4;
            return a + 9;
        }
    }  
    return 0;
}

void Interpreter::handle_operand(std::string::iterator & it, std::string::iterator & end){
    long a = get_num(it, end);
        //std::cout << "number = " << a << std::endl;
    if(a >= -INT32_MAX && a <= INT32_MAX ){             // is operand
        _stk.push((int)a);
        //std::cout << "<ok" << std::endl;
    }
}

Command* Interpreter::get_cmd(std::string::iterator& it, std::string::iterator & end){
    std::stringstream result;
    Context context = {result, _stack};
    while (it != end) {
        char c = *it;
        if (std::is_digit(c)) {
            int n = read_number(it);
            stack.push(n);
        }
        else if (std::is_whitespace(c)) {
            continue;
        }
        std::string cmd = read_until_space(it);
        auto cmd_it = my_creator.find(cmd);
        if (cmd_it == my_creator.end()) {
            // TODO: print error
            return;
        }
        *cmd_it->second.apply(context);
        it++;
    }
}

Command* Interpreter::get_cmd(std::string::iterator& it, std::string::iterator & end){
    long long a = get_command(it, end); 
    if(a - INT32_MAX == 17){info.is_print = true;}   //print
    else if(a - INT32_MAX == 13){info.is_cr = true;}
    else if(a - INT32_MAX == 8 || a - INT32_MAX == 12){info.is_point_or_emit = true;}
    std::map<int, creator_t>::iterator creator_it = my_creator.find((int)(a - INT32_MAX));            // find command
    creator_t creator = (*creator_it).second;
    return creator();
}

void Interpreter::handle_cmd(std::string::iterator& it, std::string::iterator & end){
    Command* cmd = get_cmd(it, end);

    if(info.is_print == true){
        cmd->print(it , end, result);
        info.is_print = false;
    }
    if(info.is_cr == true){
        cmd->apply(result);
        info.is_cr = false;
    } 
    if(info.is_point_or_emit == true){
        cmd->apply(_stk, result);
        info.is_point_or_emit = false;
    } 
    else {
        cmd->apply(_stk);
    }
}

void Interpreter::interpret(std::string& exp){
    result.clear();
    info.clear();
    std::string::iterator it = exp.begin();     
    std::string::iterator end = exp.end();
    bool flag = true;
    while(true){
        try{
            if(is_cmd(it, end)) {
                handle_cmd(it, end);
                info.c_cmd++;
            }

            else if(is_digit(it,end)) {
                handle_operand(it, end);
                info.c_operands++;
            }

            else if ((*it) == ' '){it++;}

            else if(it == end)  {
                break;
            }

            else {
                it++;

                if(flag) {
                    flag = false;
                    throw Interpreter_error("no such command\n");
                }

            }

        }catch(Interpreter_error& e){
            info.c_exep++;
            result.append(e.what());
            //std::cout << e.what() << std::endl;
        }
    }

    if(info.c_exep == 0 && info.c_cmd == 0 && info.c_operands > 0){
        //std::cout<< "<ok" << std::endl;
        result.append("< ok\n");
    }
    //std::cout << _stk;
}