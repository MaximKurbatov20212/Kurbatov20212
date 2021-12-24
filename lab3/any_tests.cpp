#include <gtest/gtest.h>
#include <string>
#include "any.hpp"

// Move Ctor
TEST(any_tests, test_move_ctor){
    utils::Any a = 10;
    EXPECT_TRUE(a.type() == typeid(int));
    std::cout << a.get_value<int>();

    utils::Any a2 = 10.1;
    EXPECT_TRUE(a2.type() == typeid(double));
    // EXPECT_TRUE(a2.get_value<double>() == 10.1);

    // utils::Any a3 = "hello";
    // EXPECT_TRUE(a3.type() == typeid(std::string));
    // EXPECT_TRUE(a3.get_value<std::string>() == "hello");
}


TEST(any_tests, test_copy_ctor){
    const int v = 10;
    utils::Any a = v;
    EXPECT_TRUE(a.type() == typeid(int));
    // EXPECT_TRUE(a.get_value<int>() == 10);

    const double v1 = 10.1;
    utils::Any a2 = v1;
    EXPECT_TRUE(a2.type() == typeid(double));
    // EXPECT_TRUE(a2.get_value<double>() == 10.1);

    // std::string v3 = "hello";
    // utils::Any a3 = v3;
    // EXPECT_TRUE(a3.type() == typeid(std::string));
    // EXPECT_TRUE(a3.get_value<std::string>() == "hello");

    const int* v4 = new int(4);
    utils::Any a4 = v4;
    EXPECT_TRUE(a4.type() == typeid(int*));
    EXPECT_TRUE(*(a4.get_value<int*>()) == *v4);
}