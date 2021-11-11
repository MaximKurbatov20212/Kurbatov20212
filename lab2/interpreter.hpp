#ifndef INTERPRETER
#define INTERPRETER

class Interpreter{
public:
    void interpret(std::string& exp);

private:
    bool is_num(std::string& exp);
    bool is_cmd(std::string& exp);
    bool is_digit(char& sth);
    std::stack <int> stk_; 
};


#endif