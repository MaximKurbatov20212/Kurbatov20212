#include <gtest/gtest.h>
#include"interpreter.hpp"
#include"command.hpp"
#include"my_stack.hpp"

TEST(interpreter_test, ewq ){
    std::string exp = "1";
    Interpreter interpreter = Interpreter::get_instance();
    interpreter.interpret(exp);
    
    EXPECT_EQ(,"<ok");
}
