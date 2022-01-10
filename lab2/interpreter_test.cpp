#include <gtest/gtest.h>
#include"interpreter.hpp"
#include"command.hpp"
#include"my_stack.hpp"

// Push
TEST(interpreter_test, push_one_positive_number ){
    std::string exp = "1 .";
    Interpreter interpreter = Interpreter::get_instance();

    EXPECT_EQ(interpreter.interpret(exp), "1 < ok\n");  
}

TEST(interpreter_test, push_many_positive_number ){
    std::string exp = "1 2 3 4 5 . . . . .";
    Interpreter interpreter = Interpreter::get_instance();
      
    EXPECT_EQ(interpreter.interpret(exp), "5 4 3 2 1 < ok\n");  
}

TEST(interpreter_test, push_multi_digit_positive_number ){
    std::string exp = "2147483647 .";
    Interpreter interpreter = Interpreter::get_instance();

    EXPECT_EQ(interpreter.interpret(exp), "2147483647 < ok\n");  
}


TEST(interpreter_test, push_negative_number ){
    std::string exp = "-1 .";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "-1 < ok\n");  
}


TEST(interpreter_test, push_many_negative_number ){
    std::string exp = "-1 -4 -1 -7 . . . .";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "-7 -1 -4 -1 < ok\n");  
}


TEST(interpreter_test, push_multi_digit_negative_number ){
    std::string exp = "-2147483648 ."; // INT32_MIN
    Interpreter interpreter = Interpreter::get_instance();

    EXPECT_EQ(interpreter.interpret(exp), "-2147483648 < ok\n");  

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
}    


TEST(interpreter_test, div_by_zero ){
    std::string exp = "1 0 /";
    Interpreter interpreter = Interpreter::get_instance();
      

    EXPECT_EQ(interpreter.interpret(exp), "division by zero\n");

    exp = "1 2 3 4 5 6 -1 0 /";
      
    EXPECT_EQ(interpreter.interpret(exp), "division by zero\n");
}    

TEST(interpreter_test, command_Add_cannot_be_used ){
    std::string exp = "+";
    Interpreter interpreter = Interpreter::get_instance();
      
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 +";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Sub_cannot_be_used ){
    std::string exp = "-";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 -";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");
}    

TEST(interpreter_test, command_Mul_cannot_be_used ){
    std::string exp = "*";
    Interpreter interpreter = Interpreter::get_instance();

    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 *";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = ". -43265 -14821 - *";
    
    EXPECT_EQ(interpreter.interpret(exp), "1 too few elements\n");
}   

TEST(interpreter_test, command_Div_cannot_be_used ){
    std::string exp = "/";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 /";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = ". -43265 -14821 - /";
    
    EXPECT_EQ(interpreter.interpret(exp), "1 too few elements\n");
}    

TEST(interpreter_test, command_Mod_cannot_be_used ){
    std::string exp = "mod";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 mod";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = ". -43265 -14821 - mod";
    
    EXPECT_EQ(interpreter.interpret(exp), "1 too few elements\n");
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
    
    EXPECT_EQ(interpreter.interpret(exp), "-1 -3 too few elements\n");
}    

TEST(interpreter_test, command_Rot_cannot_be_used ){
    std::string exp = "rot";
    Interpreter interpreter = Interpreter::get_instance();

    EXPECT_EQ(interpreter.interpret(exp) , "too few elements\n");

    exp = "1 rot";
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = ". 1 3213 rot";
    EXPECT_EQ(interpreter.interpret(exp), "1 too few elements\n");
}    

TEST(interpreter_test, command_Over_cannot_be_used ){
    std::string exp = "over";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = "1 over";
    
    EXPECT_EQ(interpreter.interpret(exp), "too few elements\n");

    exp = ". 423432 3213 + over";
    EXPECT_EQ(interpreter.interpret(exp), "1 too few elements\n");
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
    std::string exp = ".\" foo\\\""; // ." foo\""
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "closing quote is missing\n");
}    

// Command

//Add
TEST(interpreter_test, Add_positive_numbers){
    std::string exp = "1 1 + .";
    Interpreter interpreter = Interpreter::get_instance();

    EXPECT_EQ(interpreter.interpret(exp), "2 < ok\n");

    exp = "1 1 + 2 + 2 + .";
    EXPECT_EQ(interpreter.interpret(exp), "6 < ok\n");
}   

TEST(interpreter_test, Add_negative_numbers){
    std::string exp = "-1 -1 + .";
    Interpreter interpreter = Interpreter::get_instance();
    EXPECT_EQ(interpreter.interpret(exp), "-2 < ok\n");

    exp = "-1 1 + -9 5 + ."; 
    EXPECT_EQ(interpreter.interpret(exp), "-4 < ok\n");
}    

TEST(interpreter_test, Add_multi_digit_numbers){
    std::string exp = "-132134 8321 + .";
    Interpreter interpreter = Interpreter::get_instance();
    EXPECT_EQ(interpreter.interpret(exp), "-123813 < ok\n");

    exp = "-1123 323 + -9231 + .";  
    EXPECT_EQ(interpreter.interpret(exp), "-10031 < ok\n");
}    

//Sub
TEST(interpreter_test, Sub_positive_numbers){
    std::string exp = "1 1 - .";
    Interpreter interpreter = Interpreter::get_instance();
    EXPECT_EQ(interpreter.interpret(exp), "0 < ok\n");

    exp = "1 1 - 2 - 2 - .";
    EXPECT_EQ(interpreter.interpret(exp), "-4 < ok\n");
}  

TEST(interpreter_test, Sub_negative_numbers){
    std::string exp = "-1 -1 - .";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "0 < ok\n");
    
    exp = "-1 1 - -9 5 - - .";
    EXPECT_EQ(interpreter.interpret(exp), "12 < ok\n");
}    

TEST(interpreter_test, Sub_multi_digit_numbers){
    std::string exp = "-2367 -3214 - .";
    Interpreter interpreter = Interpreter::get_instance();

    EXPECT_EQ(interpreter.interpret(exp), "847 < ok\n");
    exp = "-231 43 - -9541 - .";
   
    EXPECT_EQ(interpreter.interpret(exp), "9267 < ok\n");
}    

// Mul
TEST(interpreter_test, Mul_positive_numbers){
    std::string exp = "1 2 * .";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "2 < ok\n");
    
    exp = "1 1 * 2 * 5 * .";
   
    EXPECT_EQ(interpreter.interpret(exp), "10 < ok\n");
}  

TEST(interpreter_test, Mul_negative_numbers){
    std::string exp = "-1 -1 - .";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "0 < ok\n");

    exp = "-1 9 * -7 1 * * .";
   
    EXPECT_EQ(interpreter.interpret(exp), "63 < ok\n");
}    

TEST(interpreter_test, Mul_multi_digit_numbers){
    std::string exp = "-2367 231 * .";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "-546777 < ok\n");
    
    exp = "-223 4 * -2341 * .";
   
    EXPECT_EQ(interpreter.interpret(exp), "2088172 < ok\n");
}    

TEST(interpreter_test, Mod_numbers){
    std::string exp = "-2367 231 mod .";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "-57 < ok\n");
    
    exp = "-223 4 mod -2341 mod .";
   
    EXPECT_EQ(interpreter.interpret(exp), "-3 < ok\n");    
}    

TEST(interpreter_test, test_dup){
    std::string exp = "2 3 4 1 dup . . . . .";
    Interpreter interpreter = Interpreter::get_instance();
    
    EXPECT_EQ(interpreter.interpret(exp), "1 1 4 3 2 < ok\n");
    
    exp = "2 3 + dup 2 . . .";
   
    EXPECT_EQ(interpreter.interpret(exp), "2 5 5 < ok\n");
    

    exp = "-1 dup . .";

    EXPECT_EQ(interpreter.interpret(exp), "-1 -1 < ok\n");
}    

TEST(interpreter_test, test_drop){
    Interpreter interpreter = Interpreter::get_instance();

    std::string exp = "2 3 4 1 drop . . .";
    
    EXPECT_EQ(interpreter.interpret(exp), "4 3 2 < ok\n");
    
    exp = "2 3 + dup 2 drop . .";
   
    EXPECT_EQ(interpreter.interpret(exp), "5 5 < ok\n");

    exp = "-1 -2 drop .";
   
    EXPECT_EQ(interpreter.interpret(exp), "-1 < ok\n");    
}    

TEST(interpreter_test, test_swap){
    Interpreter interpreter = Interpreter::get_instance();

    std::string exp = "2 3 swap . .";
    
    EXPECT_EQ(interpreter.interpret(exp), "2 3 < ok\n");
 
    exp = "-321321  32133123 swap . .";
   
    EXPECT_EQ(interpreter.interpret(exp), "-321321 32133123 < ok\n");

    exp = "1 2 -3 swap . . .";
   
    EXPECT_EQ(interpreter.interpret(exp), "2 -3 1 < ok\n");

}   

TEST(interpreter_test, test_rot){
    Interpreter interpreter = Interpreter::get_instance();

    std::string exp = "1 2 -3 4 rot . . . .";
    
    EXPECT_EQ(interpreter.interpret(exp), "-3 2 4 1 < ok\n");

    exp = "-321321  32133123 23 rot -93212 . . . .";
   
    EXPECT_EQ(interpreter.interpret(exp), "-93212 32133123 -321321 23 < ok\n"); 
}  

TEST(interpreter_test, test_over){
    Interpreter interpreter = Interpreter::get_instance();

    std::string exp = "1 2 -3 4 over . . . . .";
    
    EXPECT_EQ(interpreter.interpret(exp), "-3 4 -3 2 1 < ok\n");
    
    exp = "-321321  32133123 23 over -93212 . . . . .";
   
    EXPECT_EQ(interpreter.interpret(exp), "-93212 32133123 23 32133123 -321321 < ok\n");    
}   

TEST(interpreter_test, test_emit){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "12321 emit";
    EXPECT_EQ(interpreter.interpret(exp), "number on stack is out of ASCII range and cannot be displayed\n");
    
    exp = "-1 2 3 65 emit";
    EXPECT_EQ(interpreter.interpret(exp), "A\n< ok\n");
    
    exp = "213 213 97 emit";
    EXPECT_EQ(interpreter.interpret(exp), "a\n< ok\n");
}   


TEST(interpreter_test, test_cr){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "-1 2 . cr";
    
    EXPECT_EQ(interpreter.interpret(exp), "2 \n< ok\n");
}   

TEST(interpreter_test, test_greater){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "-1 2 > .";
    
    EXPECT_EQ(interpreter.interpret(exp), "0 < ok\n");
    
    exp = "321321 321321 > .";
   
    EXPECT_EQ(interpreter.interpret(exp), "0 < ok\n");
    

    exp = "32121321 -321321 > .";
   
    EXPECT_EQ(interpreter.interpret(exp), "1 < ok\n");
    
}   

TEST(interpreter_test, test_less){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "-1 2 < .";
    
    EXPECT_EQ(interpreter.interpret(exp), "1 < ok\n");

    exp = "321321 321321 < .";
   
    EXPECT_EQ(interpreter.interpret(exp), "0 < ok\n");
    

    exp = "32121321 -321321 < .";
   
    EXPECT_EQ(interpreter.interpret(exp), "0 < ok\n");
}   

TEST(interpreter_test, test_equal){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "-1 2 = .";
    
    EXPECT_EQ(interpreter.interpret(exp), "0 < ok\n");
    
    exp = "321321 321321 = .";
    EXPECT_EQ(interpreter.interpret(exp), "1 < ok\n");
    
    exp = "32121321 -321321 = .";
    EXPECT_EQ(interpreter.interpret(exp), "0 < ok\n");
}   

TEST(interpreter_test, test_print){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = ".\" hello\"";
    EXPECT_EQ(interpreter.interpret(exp), "hello\n< ok\n");

    exp = ".\" 321321hewqhj\"";
    EXPECT_EQ(interpreter.interpret(exp), "321321hewqhj\n< ok\n");
    
    exp = ".\" hdsa    \"";
    EXPECT_EQ(interpreter.interpret(exp), "hdsa    \n< ok\n");

    exp = ".\" foo\\foo\"";
    EXPECT_EQ(interpreter.interpret(exp), "can't escape f\n");

    exp = ".\" foo\\\"\"";
    EXPECT_EQ(interpreter.interpret(exp), "foo\"\n< ok\n");
}   

//
TEST(interpreter_test, too_many_spaces){
    Interpreter interpreter = Interpreter::get_instance();
    std::string exp = "   1              2   . .";
    
    EXPECT_EQ(interpreter.interpret(exp), "2 1 < ok\n");

    exp = "   -21    212   238939  -312 . . . .";
    
    EXPECT_EQ(interpreter.interpret(exp), "-312 238939 212 -21 < ok\n");
    
    exp = "   1    -1    +  .";
    EXPECT_EQ(interpreter.interpret(exp), "0 < ok\n");
}   

TEST(interpreter_test, numbers_starting_at_zero){
    Interpreter interpreter = Interpreter::get_instance();
    
    std::string exp = "01 .";
    EXPECT_EQ(interpreter.interpret(exp), "1 < ok\n");

    exp = "00000000000001 .";
    EXPECT_EQ(interpreter.interpret(exp), "1 < ok\n");

    exp = "-00000000000001 .";
    EXPECT_EQ(interpreter.interpret(exp), "-1 < ok\n");

    exp = "001 000001 + .";
    EXPECT_EQ(interpreter.interpret(exp), "2 < ok\n");
}   

TEST(interpreter_test, sub_is_correct){
    Interpreter interpreter = Interpreter::get_instance();
    
    std::string exp = "1 2 -.";
    EXPECT_EQ(interpreter.interpret(exp), "no such command\n");
    
    exp = "1 2 ..";
    EXPECT_EQ(interpreter.interpret(exp), "no such command\n");

    exp = "1 2 -. 1";
    EXPECT_EQ(interpreter.interpret(exp), "no such command\n");
}  

