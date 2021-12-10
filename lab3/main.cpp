#include "any.hpp"
int main(){
    std::string a_3 = "sad";

    Any m = a_3;

    float a_1 = 1.7;

    const int b_1 = 2;

    Any a = 5;  // CopyCtor Any Move
    Any b = 10; // CopyCtor Any Move
    
    Any c(5);   // CopyCtor Any Move

    Any d(a_1); // CopyCtor Any Move


    Any e(b_1); // CopyCtor Any

    a = b;

    swap(c, d);

    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << m << std::endl;

    Any t;
    t.any_cast<int>(&a);
} 