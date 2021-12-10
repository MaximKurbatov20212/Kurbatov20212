#include "any.hpp"

template<typename T>
Any::Any(const T& value):  storage_(new B<T>(value))  {
    std::cout << "CopyCtor Any" << std::endl;
}   

template<typename T>
Any::Any(T&& value){
    if (storage_ == nullptr) delete storage_;
    storage_ = std::move(new B<T>(value));
    std::cout << "CopyCtor Any Move" << std::endl;
}   

Any::~Any(){
    delete storage_;
    std::cout << "Dtor Any" << std::endl;
} 

void Any::operator=(Any& other){
    std::cout << "op=" << std::endl;
    if (storage_ == nullptr) delete storage_;
    storage_ = other.storage_->get_value();
}

template<typename T>
void Any::operator=(T& value){
    if (storage_ == nullptr) delete storage_;
    storage_(value);
} 

template<typename T> 
T Any::any_cast(Any* a){  
    T tmp = 
    return static_cast<T>(tmp);
}

void swap(Any& a, Any& b){
    std::cout << "swap" << std::endl;
    std::swap(a.storage_, b.storage_);
}

std::ostream& operator<<(std::ostream &out, Any& a){
    a.storage_->print_info(); 
    return out;
}  
