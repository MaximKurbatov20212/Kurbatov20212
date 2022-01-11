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
    EXPECT_TRUE(utils::any_cast<int>(&a) == 10);

    utils::Any a2 = 10.1;
    EXPECT_TRUE(utils::any_cast<double>(&a2) == 10.1);
}

// Copy Ctor
TEST(any_tests, test_copy_ctor_std_types){
    const int v = 10;
    utils::Any a = v;
    EXPECT_TRUE(utils::any_cast<const int>(&a) == 10);


    const double v1 = 10.1;
    utils::Any a2 = v1;
    EXPECT_TRUE(utils::any_cast<const double>(&a2) == 10.1);


    const std::string v3 = "hello";
    utils::Any a3 = v3;
    EXPECT_TRUE(utils::any_cast<const std::string>(&a3) == "hello");


    const int* v4 = new int(4);
    utils::Any a4 = v4;
    EXPECT_TRUE(utils::any_cast<const int*>(&a4) == v4);

    const char* v5 = new char('a');
    utils::Any a5 = v5;
    EXPECT_TRUE(utils::any_cast<const char*>(&a5) == v5);


    const double* v6 = new double(1.2);
    utils::Any a6 = v6;
    EXPECT_TRUE(utils::any_cast<const double*>(&a6) == v6);

    delete v6;
    delete v5;
    delete v4;
}

//Swap
TEST(any_tests, test_swap){
    utils::Any a = 10;
    utils::Any b = 22.2;
    swap(a, b);

    EXPECT_TRUE(utils::any_cast<double>(&a) == 22.2);

    EXPECT_TRUE(utils::any_cast<int>(&b) == 10);


    std::string str = "hello";
    utils::Any c = str;
    swap(c, b);

    EXPECT_TRUE(utils::any_cast<int>(&c) == 10);

    EXPECT_TRUE(utils::any_cast<std::string>(&b) == "hello");
}

// op=(Any)
TEST(any_tests, copy_assigment){
    std::string str = "foo";
    Point* p = new Point(4,3);
    utils::Any a = 10;
    utils::Any a1 = str;
    utils::Any a2 = p;

    utils::Any b;
    b = a;
    EXPECT_TRUE(utils::any_cast<int>(&b) == 10);

    b = a1;
    EXPECT_TRUE(utils::any_cast<std::string>(&b) == str);
    
    b = a2;
    EXPECT_TRUE(*(utils::any_cast<Point*>(&b)) == *p);

    delete p;
}

// Ctor Any to Any
TEST(any_tests, copy_any_to_any){
    std::string str = "foo";
    int* p = new int(4);
    
    utils::Any a = 10;
    utils::Any a1 = str;
    utils::Any a2 = p;

    utils::Any b2 = a2;
    EXPECT_TRUE(*(utils::any_cast<int*>(&b2)) == *p);
    EXPECT_TRUE(*(utils::any_cast<int*>(&a2)) == *p);
    delete p;

    utils::Any b = a;
    EXPECT_TRUE(utils::any_cast<int>(&b) == 10);
    EXPECT_TRUE(utils::any_cast<int>(&a) == 10);
    
    utils::Any b1 = a1;
    EXPECT_TRUE(utils::any_cast<std::string>(&b1) == str);
    EXPECT_TRUE(utils::any_cast<std::string>(&a1) == str);
}

// op=(Value& v)
TEST(any_tests, assigment_any_to_any){
    int v = 10;
    utils::Any a;
    a = v;
    EXPECT_TRUE(utils::any_cast<int>(&a) == 10);


    double v1 = 10.1;
    utils::Any a2;
    a2 = v1;
    EXPECT_TRUE(utils::any_cast<double>(&a2) == 10.1);


    std::string v3 = "hello";
    utils::Any a3;
    a3 = v3;
    EXPECT_TRUE(utils::any_cast<std::string>(&a3) == "hello");


    int* v4 = new int(4);
    utils::Any a4;
    a4 = v4;
    EXPECT_TRUE(*(utils::any_cast<int*>(&a4)) == *v4);
    delete v4;

    double* v6 = new double(1.2);
    utils::Any a6;
    a6 = v6;
    EXPECT_TRUE(*(utils::any_cast<double*>(&a6)) == *v6);
    delete v6;    

    Point* v7 = new Point(1, 2);
    utils::Any a7;
    a7 = v7;
    EXPECT_TRUE(*(utils::any_cast<Point*>(&a7)) == *v7);
    delete v7;   
}

TEST(any_tests, test_bad_any_cast_just_T){
    utils::Any a = 10;
    ASSERT_THROW(utils::any_cast<std::string>(&a), utils::any_cast_error);
    ASSERT_THROW(utils::any_cast<double>(&a), utils::any_cast_error);
    ASSERT_THROW(utils::any_cast<const int>(&a), utils::any_cast_error);
    ASSERT_THROW(utils::any_cast<int*>(&a), utils::any_cast_error);
    ASSERT_THROW(utils::any_cast<char>(&a), utils::any_cast_error);
    ASSERT_THROW(utils::any_cast<const char>(&a), utils::any_cast_error);
}

TEST(any_tests, test_bad_any_cast_pointer_to_T){
    const utils::Any a = 10;
    ASSERT_THROW(utils::any_cast<std::string>(&a), utils::any_cast_error);
    ASSERT_THROW(utils::any_cast<double>(&a), utils::any_cast_error);
    ASSERT_THROW(utils::any_cast<const int>(&a), utils::any_cast_error);
    ASSERT_THROW(utils::any_cast<int*>(&a), utils::any_cast_error);
    ASSERT_THROW(utils::any_cast<char>(&a), utils::any_cast_error);
    ASSERT_THROW(utils::any_cast<const char>(&a), utils::any_cast_error);
}

TEST(any_tests, test_any_cast_pointer_to_T){
    const utils::Any a = 10;  
    EXPECT_TRUE(*(utils::any_cast<int>(a)) == 10);

    const utils::Any a2 = 10.1;
    EXPECT_TRUE(*(utils::any_cast<double>(a2)) == 10.1);

    int* p = new int(5);
    const utils::Any a4 = p;
    EXPECT_TRUE(*(utils::any_cast<int*>(a4)) == p);
    delete p;
}
