#include <gtest/gtest.h>
#include"interpreter.hpp"
#include"command.hpp"
#include"my_stack.hpp"

// Push
TEST(interpreter_test, push_one_positive_number ){
    std::string exp = "1";
    Interpreter interpreter = Interpreter::get_instance();

    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");  
    EXPECT_EQ(interpreter._stk.top(), 1);
}

TEST(interpreter_test, push_many_positive_number ){
    std::string exp = "1 2 3 4 5";
    Interpreter interpreter = Interpreter::get_instance();
      

    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");  
    EXPECT_EQ(interpreter._stk.pop(), 5);
    EXPECT_EQ(interpreter._stk.pop(), 4);
    EXPECT_EQ(interpreter._stk.pop(), 3);
    EXPECT_EQ(interpreter._stk.pop(), 2);
    EXPECT_EQ(interpreter._stk.pop(), 1);
}

TEST(interpreter_test, push_multi_digit_positive_number ){
    std::string exp = "2147483647";
    Interpreter interpreter = Interpreter::get_instance();


    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");  
    EXPECT_EQ(interpreter._stk.pop(), 2147483647);
}


TEST(interpreter_test, push_negative_number ){
    std::string exp = "-1";
    Interpreter interpreter = Interpreter::get_instance();
      

    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");  
    EXPECT_EQ(interpreter._stk.pop(), -1);
}


TEST(interpreter_test, push_many_negative_number ){
    std::string exp = "-1 -4 -1 -7";
    Interpreter interpreter = Interpreter::get_instance();
      

    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");  
    EXPECT_EQ(interpreter._stk.pop(), -7);
    EXPECT_EQ(interpreter._stk.pop(), -1);
    EXPECT_EQ(interpreter._stk.pop(), -4);
    EXPECT_EQ(interpreter._stk.pop(), -1);
}


TEST(interpreter_test, push_multi_digit_negative_number ){
    std::string exp = "-2147483648"; // INT32_MIN
    Interpreter interpreter = Interpreter::get_instance();

    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");  
    EXPECT_EQ(interpreter._stk.pop(), -2147483648);

    exp = "-2147483649";    // error
    EXPECT_EQ(interpreter.interpret(exp), "out of range of int\n");  
}

// Without exeptions

TEST(interpreter_test, push_number_greater_then_INT32_MAX ){
    std::string exp = "10000000000000000000000";
    Interpreter interpreter = Interpreter::get_instance();
      
    EXPECT_EQ(interpreter.interpret(exp), "out of range of int\n");
} 

TEST(interpreter_test, push_number_less_then_minus_INT32_MAX ){
    std::string exp = "-10000000000000000000000";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "out of range of int\n");
    
}     

TEST(interpreter_test, push_unkown_symbol ){
    std::string exp = "swa";
    Interpreter interpreter = Interpreter::get_instance();
      
    
    EXPECT_EQ(interpreter.interpret(exp), "no such command\n");
    
    // exp.clear();
    // exp = "   dasweqew   ";
      
    // EXPECT_EQ(interpreter.interpret(exp), "no such command\n");
}    


TEST(interpreter_test, div_by_zero ){
    std::string exp = "1 0 /";
    Interpreter interpreter = Interpreter::get_instance();
      

    EXPECT_EQ(interpreter.interpret(exp), "division by zero\n");
    interpreter._stk.pop();

    exp = "1 2 3 4 5 6 -1 0 /";
      
    EXPECT_EQ(interpreter.interpret(exp), "division by zero\n");
}    

TEST(interpreter_test, command_Add_cannot_be_used ){
    std::string exp = "+";
    Interpreter interpreter = Interpreter::get_instance();
      
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 +";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
    interpreter._stk.pop();
}    

TEST(interpreter_test, command_Sub_cannot_be_used ){
    std::string exp = "-";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 -";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
    interpreter._stk.pop();
}    

TEST(interpreter_test, command_Mul_cannot_be_used ){
    std::string exp = "*";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 *";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
    interpreter._stk.pop();

    exp = "-43265 -14821 - *";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}   

TEST(interpreter_test, command_Div_cannot_be_used ){
    std::string exp = "/";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 /";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
    interpreter._stk.pop();

    exp = "-43265 -14821 - /";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Mod_cannot_be_used ){
    std::string exp = "mod";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 mod";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
    interpreter._stk.pop();

    exp = "-43265 -14821 - mod";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Dup_cannot_be_used ){
    std::string exp = "dup";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 1 + drop dup";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Drop_cannot_be_used ){
    std::string exp = "drop";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 1 drop drop drop";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Point_cannot_be_used ){
    std::string exp = ".";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "-3 -1 . . .";
    
    EXPECT_EQ(interpreter.interpret(exp), "-1-3too few elements\n");
}    

TEST(interpreter_test, command_Rot_cannot_be_used ){
    std::string exp = "rot";
    Interpreter interpreter = Interpreter::get_instance();

    EXPECT_EQ(interpreter.interpret(exp) , "too few elements\n");

    exp = "1 rot";
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
    interpreter._stk.pop();

    exp = "1 3213 rot";
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Over_cannot_be_used ){
    std::string exp = "over";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 over";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
    interpreter._stk.pop();

    exp.clear();
    exp = "423432 3213 + over";
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Emit_cannot_be_used ){
    std::string exp = "emit";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Greater_cannot_be_used ){
    std::string exp = ">";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "-2311 >";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Less_cannot_be_used ){
    std::string exp = "<";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "123321 <";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Equal_cannot_be_used ){
    std::string exp = "=";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "3489 =";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Print_without_closing_bracket){
    std::string exp = ".\"123";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "closing bracket is missing\n");
}    

// Command

//Add
TEST(interpreter_test, Add_positive_numbers){
    std::string exp = "1 1 +";
    Interpreter interpreter = Interpreter::get_instance();
    
    std::string res = interpreter.interpret(exp);

    EXPECT_EQ(interpreter._stk.pop(), 2);
    interpreter._stk.clear();

    exp = "1 1 + 2 + 2 +";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), 6);
}   

TEST(interpreter_test, Add_negative_numbers){
    std::string exp = "-1 -1 +";
    Interpreter interpreter = Interpreter::get_instance();
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -2);
    interpreter._stk.clear();

    exp = "-1 1 + -9 5 +";
    res = interpreter.interpret(exp);    
    EXPECT_EQ(interpreter._stk.pop(), -4);
}    

TEST(interpreter_test, Add_multi_digit_numbers){
    std::string exp = "-132134 8321 +";
    Interpreter interpreter = Interpreter::get_instance();
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -132134 + 8321);
    interpreter._stk.clear();

    exp = "-1123 323 + -9231 +";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -1123 + 323 + (-9231));
    interpreter._stk.clear();
}    

//Sub
TEST(interpreter_test, Sub_positive_numbers){
    std::string exp = "1 1 -";
    Interpreter interpreter = Interpreter::get_instance();
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), 0);
    interpreter._stk.clear();

    exp = "1 1 - 2 - 2 -";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), (1 - 1) - 2 - 2 );
}  

TEST(interpreter_test, Sub_negative_numbers){
    std::string exp = "-1 -1 -";
    Interpreter interpreter = Interpreter::get_instance();
    std::string res = interpreter.interpret(exp);
    
    EXPECT_EQ(interpreter._stk.pop(), 0);
    interpreter._stk.clear();

    exp = "-1 1 - -9 5 - -";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), (-1 - 1) - (-9 - 5));
}    

TEST(interpreter_test, Sub_multi_digit_numbers){
    std::string exp = "-2367 -3214 -";
    Interpreter interpreter = Interpreter::get_instance();
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -2367 - (-3214));
    interpreter._stk.clear();

    exp = "-231 43 - -9541 -";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -231 - 43 - (-9541));
    interpreter._stk.clear();
}    


// Mul
TEST(interpreter_test, Mul_positive_numbers){
    std::string exp = "1 2 *";
    Interpreter interpreter = Interpreter::get_instance();
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), 2);
    interpreter._stk.clear();

    exp = "1 1 * 2 * 5 *";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), (1 * 1) * 2 * 5 );
}  

TEST(interpreter_test, Mul_negative_numbers){
    std::string exp = "-1 -1 -";
    Interpreter interpreter = Interpreter::get_instance();
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), 0);
    interpreter._stk.clear();

    exp = "-1 9 * -7 1 * *";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), (-1 * 9) * (-7 * 1));
}    

TEST(interpreter_test, Mul_multi_digit_numbers){
    std::string exp = "-2367 231 *";
    Interpreter interpreter = Interpreter::get_instance();
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -2367 * 231);
    interpreter._stk.clear();

    exp = "-223 4 * -2341 *";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -223 * 4 * (-2341));
    interpreter._stk.clear();
}    

TEST(interpreter_test, Mod_numbers){
    std::string exp = "-2367 231 mod";
    Interpreter interpreter = Interpreter::get_instance();
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -2367 % 231);
    interpreter._stk.clear();

    exp = "-223 4 mod -2341 mod";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), (-223 % 4) % (-2341));
    interpreter._stk.clear();
}    

TEST(interpreter_test, test_dup){
    std::string exp = "2 3 4 1 dup";
    Interpreter interpreter = Interpreter::get_instance();
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), 1);
    EXPECT_EQ(interpreter._stk.pop(), 1);
    EXPECT_EQ(interpreter._stk.pop(), 4);
    EXPECT_EQ(interpreter._stk.pop(), 3);
    EXPECT_EQ(interpreter._stk.pop(), 2);
    interpreter._stk.clear();

    exp = "2 3 + dup 2";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), 2);
    EXPECT_EQ(interpreter._stk.pop(), 5);
    EXPECT_EQ(interpreter._stk.pop(), 5);
    interpreter._stk.clear();

    exp = "-1 dup";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -1);
    EXPECT_EQ(interpreter._stk.pop(), -1);
    interpreter._stk.clear();
}    

TEST(interpreter_test, test_drop){
    Interpreter interpreter = Interpreter::get_instance();

    std::string exp = "2 3 4 1";
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");
    
    exp = "drop";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), 4);
    EXPECT_EQ(interpreter._stk.pop(), 3);
    EXPECT_EQ(interpreter._stk.pop(), 2);
    interpreter._stk.clear();

    exp = "2 3 + dup 2 drop";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), 5);
    EXPECT_EQ(interpreter._stk.pop(), 5);
    interpreter._stk.clear();

    exp = "-1 -2 drop";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -1);
    interpreter._stk.clear();
}    

TEST(interpreter_test, test_point){
    Interpreter interpreter = Interpreter::get_instance();

    std::string exp = "2 3 4 1 .";
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter.interpret(exp), "1< ok\n");
    EXPECT_EQ(interpreter._stk.pop(), 4);
    EXPECT_EQ(interpreter._stk.pop(), 3);
    EXPECT_EQ(interpreter._stk.pop(), 2);
    interpreter._stk.clear();

    exp = "-1  32133123 .";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter.interpret(exp), "32133123< ok\n");
    EXPECT_EQ(interpreter._stk.pop(), -1);
    interpreter._stk.clear();
}    

TEST(interpreter_test, test_swap){
    Interpreter interpreter = Interpreter::get_instance();

    std::string exp = "2 3 swap";
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), 2);
    EXPECT_EQ(interpreter._stk.pop(), 3);
    interpreter._stk.clear();

    exp = "-321321  32133123 swap";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -321321);
    EXPECT_EQ(interpreter._stk.pop(), 32133123);
    interpreter._stk.clear();

    exp = "1 2 -3 swap";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), 2);
    EXPECT_EQ(interpreter._stk.pop(), -3);
    EXPECT_EQ(interpreter._stk.pop(), 1);
    interpreter._stk.clear();
}   

TEST(interpreter_test, test_rot){
    Interpreter interpreter = Interpreter::get_instance();

    std::string exp = "1 2 -3 4 rot";
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -3);
    EXPECT_EQ(interpreter._stk.pop(), 2);
    EXPECT_EQ(interpreter._stk.pop(), 4);
    EXPECT_EQ(interpreter._stk.pop(), 1);
    interpreter._stk.clear();

    exp = "-321321  32133123 23 rot -93212";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -93212);
    EXPECT_EQ(interpreter._stk.pop(), 32133123);
    EXPECT_EQ(interpreter._stk.pop(), -321321);
    EXPECT_EQ(interpreter._stk.pop(), 23);
    interpreter._stk.clear();
}   

TEST(interpreter_test, test_over){
    Interpreter interpreter = Interpreter::get_instance();

    std::string exp = "1 2 -3 4 over";
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -3);
    EXPECT_EQ(interpreter._stk.pop(), 4);
    EXPECT_EQ(interpreter._stk.pop(), -3);
    EXPECT_EQ(interpreter._stk.pop(), 2);
    EXPECT_EQ(interpreter._stk.pop(), 1);
    interpreter._stk.clear();

    exp = "-321321  32133123 23 over -93212";
    res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter._stk.pop(), -93212);
    EXPECT_EQ(interpreter._stk.pop(), 32133123);
    EXPECT_EQ(interpreter._stk.pop(), 23);
    EXPECT_EQ(interpreter._stk.pop(), 32133123);
    EXPECT_EQ(interpreter._stk.pop(), -321321);
    interpreter._stk.clear();
}   

TEST(interpreter_test, test_emit){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "12321 emit";
    EXPECT_EQ(interpreter.interpret(exp), "is not printed");
    interpreter._stk.clear();

    exp = "-1 2 3 65 emit";
    EXPECT_EQ(interpreter.interpret(exp), "A\n< ok\n");
    interpreter._stk.clear();

    exp = "213 213 97 emit";
    EXPECT_EQ(interpreter.interpret(exp), "a\n< ok\n");
    interpreter._stk.clear();
}   


TEST(interpreter_test, test_cr){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "-1 2 . cr .";
    std::string res = interpreter.interpret(exp);
    EXPECT_EQ(interpreter.interpret(exp), "2\n-1< ok\n");
    interpreter._stk.clear();
}   

TEST(interpreter_test, test_greater){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "-1 2 >";
    std::string res = interpreter.interpret(exp);
    EXPECT_FALSE(interpreter._stk.pop());
    interpreter._stk.clear();

    exp = "321321 321321 >";
    res = interpreter.interpret(exp);
    EXPECT_FALSE(interpreter._stk.pop());
    interpreter._stk.clear();

    exp = "32121321 -321321 >";
    res = interpreter.interpret(exp);
    EXPECT_TRUE(interpreter._stk.pop());
    interpreter._stk.clear();
}   

TEST(interpreter_test, test_less){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "-1 2 <";
    std::string res = interpreter.interpret(exp);
    EXPECT_TRUE(interpreter._stk.pop());
    interpreter._stk.clear();

    exp = "321321 321321 <";
    res = interpreter.interpret(exp);
    EXPECT_FALSE(interpreter._stk.pop());
    interpreter._stk.clear();

    exp = "32121321 -321321 <";
    res = interpreter.interpret(exp);
    EXPECT_FALSE(interpreter._stk.pop());
    interpreter._stk.clear();
}   

TEST(interpreter_test, test_equal){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "-1 2 =";
    std::string res = interpreter.interpret(exp);
    EXPECT_FALSE(interpreter._stk.pop());
    interpreter._stk.clear();

    exp = "321321 321321 =";
    res = interpreter.interpret(exp);
    EXPECT_TRUE(interpreter._stk.pop());
    interpreter._stk.clear();

    exp = "32121321 -321321 =";
    res = interpreter.interpret(exp);
    EXPECT_FALSE(interpreter._stk.pop());
    interpreter._stk.clear();
}   

TEST(interpreter_test, test_print){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = ".\"hello\"";
    EXPECT_EQ(interpreter.interpret(exp), "hello\n< ok\n");

    exp = ".\"321321hewqhj\"";
    EXPECT_EQ(interpreter.interpret(exp), "321321hewqhj\n< ok\n");
    
    exp = ".\"hdsa\"dasda\"dasjk\"    \"";
    EXPECT_EQ(interpreter.interpret(exp), "hdsa\"dasda\"dasjk\"    \n< ok\n");
}   

//
TEST(interpreter_test, too_many_spaces){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "   1              2   ";
    
    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");
    EXPECT_EQ(interpreter._stk.pop(), 2);
    EXPECT_EQ(interpreter._stk.pop(), 1);
    interpreter._stk.clear();

    exp = "   -21    212   238939  -312";
    
    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");

    EXPECT_EQ(interpreter._stk.pop(), -312);
    EXPECT_EQ(interpreter._stk.pop(), 238939);
    EXPECT_EQ(interpreter._stk.pop(), 212);
    EXPECT_EQ(interpreter._stk.pop(), -21);
    interpreter._stk.clear();

    exp = "   1    -1    +  ";
    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");
    EXPECT_EQ(interpreter._stk.pop(), 0);
    interpreter._stk.clear();
}   

TEST(interpreter_test, numbers_starting_at_zero){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "01";
    
    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");
    EXPECT_EQ(interpreter._stk.pop(), 1);
    interpreter._stk.clear();

    exp = "00000000000001";
    
    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");
    EXPECT_EQ(interpreter._stk.pop(), 1);
    interpreter._stk.clear();

    exp = "-00000000000001";
    
    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");
    EXPECT_EQ(interpreter._stk.pop(), -1);
    interpreter._stk.clear();

    exp = "001 000001 +";
    EXPECT_EQ(interpreter.interpret(exp), "< ok\n");
    EXPECT_EQ(interpreter._stk.pop(), 2);
    interpreter._stk.clear();
}   

