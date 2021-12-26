#include <gtest/gtest.h>
#include <string>
#include "any.hpp"
#include <any>

class Point{
public:    
    Point(const int& x, const int& y): x(x), y(y){}
    friend bool operator==(const Point& a, const Point& b ){
        return (a.x == b.x) && (a.y == b.y);
    }
private:    
    int x;
    int y;
};

// Move Ctor std types
TEST(any_tests, test_move_ctor_std_types){
    utils::Any a = 10;
    EXPECT_TRUE(a.type() == typeid(int));
    std::cout << (a.get_value<int>() == 10);

    utils::Any a2 = 10.1;
    EXPECT_TRUE(a2.type() == typeid(double));
    EXPECT_TRUE(a2.get_value<double>() == 10.1);


    std::string v3 = "hello";
    utils::Any a3 = v3;
    // EXPECT_TRUE(a3.type() == typeid(std::string));
    // EXPECT_TRUE(a3.get_value<std::string>() == "hello");


    int* v4 = new int(4);
    utils::Any a4 = v4;
    EXPECT_TRUE(a4.type() == typeid(int*));


    char* v5 = new char('a');
    utils::Any a5 = v5;
    EXPECT_TRUE(a5.type() == typeid(char*));

    double* v6 = new double(1.2);
    utils::Any a6 = v6;
    EXPECT_TRUE(a6.type() == typeid(double*));

    delete v6;
    delete v5;
    delete v4;
}

// Copy Ctor
TEST(any_tests, test_copy_ctor_std_types){
    const int v = 10;
    utils::Any a = v;
    EXPECT_TRUE(a.type() == typeid(int));
    EXPECT_TRUE(a.get_value<const int>() == 10);


    const double v1 = 10.1;
    utils::Any a2 = v1;
    EXPECT_TRUE(a2.type() == typeid(double));
    EXPECT_TRUE(a2.get_value<const double>() == 10.1);


    const std::string v3 = "hello";
    utils::Any a3 = v3;
    EXPECT_TRUE(a3.type() == typeid(const std::string));
    EXPECT_TRUE(a3.get_value<std::string>() == "hello");


    const int* v4 = new int(4);
    utils::Any a4 = v4;
    EXPECT_TRUE(a4.type() == typeid(const int*));
    EXPECT_TRUE(*(a4.get_value<const int*>()) == 4);


    const char* v5 = new char('a');
    utils::Any a5 = v5;
    EXPECT_TRUE(a5.type() == typeid(const char*));
    EXPECT_TRUE(*(a5.get_value<const char*>()) == 'a');


    const double* v6 = new double(1.2);
    utils::Any a6 = v6;
    EXPECT_TRUE(a6.type() == typeid(const double*));
    EXPECT_TRUE(*(a6.get_value<const double*>()) == 1.2);


    const double& v7 = 12;
    utils::Any a7 = v7;
    EXPECT_TRUE(a7.type() == typeid(const double&));


    const std::string& v8 = "hello";
    utils::Any a8 = v8;
    EXPECT_TRUE(a8.type() == typeid(const std::string&));
    delete v6;
    delete v5;
    delete v4;
}

// Move Ctor users types
TEST(any_tests, test_move_ctor_users_types){
    Point v(4, 10);
    utils::Any a = v;
    EXPECT_TRUE(a.type() == typeid(Point));
    std::cout << (a.get_value<Point>() == (Point(4, 10)));
}

TEST(any_tests, test_copy_ctor_users_types){
    const Point v(4, 10);
    utils::Any a = v;
    EXPECT_TRUE(a.type() == typeid(const Point));
    std::cout << (a.get_value<Point>() == (Point(4, 10)));
}
