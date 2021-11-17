#ifndef INTERPRETER
#define INTERPRETER

class Interpreter{
public:

    static Interpreter& get_instance(){
        static Interpreter i;
        return i;
    }

    void interpret(std::string& exp);

    get_cmd(std::string& exp);
    static std::stack<int> stk; 
private:
    int check(std::string::iterator& it, std::string::iterator& end);
    bool is_digit(std::string::iterator& it);
    long is_num(std::string::iterator& it, std::string::iterator& end);
    long is_cmd(std::string::iterator& it, std::string::iterator& end);
};
#endif