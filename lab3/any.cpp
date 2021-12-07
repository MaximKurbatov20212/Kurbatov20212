#include <iostream>
#include <typeinfo>

template<typename T> 
class Any {
public:
    Any() { std::cout << "T Ctor" << std::endl;}
    
    ~Any() { std::cout << "T Dtor" << std::endl;}

    Any(const Any & other): value_(other.value_){
        std::cout << "T CopyCtor" << std::endl;
    }

    Any(T && other): value_(other){}

    Any & operator=(const Any &);
    
    Any & operator=(const T & v ){
        value_ = v;
        return *this;
    }
    
    Any & swap(Any & other){
        std::swap(value_, other.value_);
    }

    const std::type_info & type() const{
        return typeid(T);
    }

    void print_value(){
        std::cout << value_ << std::endl;
    }
private:
    T value_;
};

template<typename T> 
class Any<T*> {
public:
    Any(): value_(new T){
        std::cout << "T* Dtor" << std::endl;
    }
    
    ~Any(){
        delete value_;
        std::cout << "D* Ctor" << std::endl;
    }

    Any(const Any & other): value_(new T){
        std::cout << "T* CopyCtor" << std::endl;
        *value_ = *(other.value_);
    }

    Any(T* &&);
    Any & operator=(const Any &);
    Any & operator=(const T* & v){
        delete value_; // ???? smart or not? user hasn't got method delete
        value_ = v;
        return *this;
    }
    Any & swap(Any & other){
        std::swap(value_, other.value_);
    }

    void print_value(){
        std::cout << value_ << std::endl;
        std::cout << *value_ << std::endl;
    }
private:
    T* value_;
};

int main(){
    Any<int> i_a;
    Any<int> i_b;

    i_a = 1;

    i_b = 2;

    i_a.print_value();
    i_b.print_value();

    i_a.swap(i_b);
    i_a.print_value();
    i_b.print_value();
    //Any<int*> ii_a(i_a); or Any ii_a(i_a);???

    Any<int*> ii_a;
    Any<int*> ii_b;
    // int a = 1;
    // int b = 2;

    // ii_a = &a;

    // ii_b = &b;

    // ii_a.print_value();
    // ii_b.print_value();

    // ii_a.swap(ii_b);
    // ii_a.print_value();
    // ii_b.print_value();

}   