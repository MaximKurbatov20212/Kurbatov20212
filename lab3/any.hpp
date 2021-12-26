#ifndef ANY
#define ANY

#include <iostream>
#include <utility>
#include <typeinfo>
#include <cassert>

namespace utils{
class Any {
public:
    Any(): storage_(nullptr){}

    template<typename T>
    Any(T& value): storage_(new Derived<T>(value))  {
        std::cout << "CopyCtor Any" << std::endl;
    }

    template<typename T>
    Any(T&& value){
        std::cout << "MoveCtor Any" << std::endl;
        if (std::is_copy_constructible_v<std::decay_t<T>> == false) throw std::runtime_error("incorrect type");
        storage_ = new Derived<T>(std::move(value));   
    }

    ~Any(){
        std::cout << "Dtor Any" << std::endl;
        if (storage_ != nullptr) delete storage_;
    } 

    void operator=(Any& other){
        std::cout << "op=" << std::endl;
        if (storage_ != nullptr) delete storage_;
        storage_ = other.storage_->get_value();
    }

    template<typename T>
    void operator=(T& value){
        if (storage_ != nullptr) delete storage_;
        storage_ = new Derived<T>(value);
    }

    bool empty() const { 
        return storage_ == nullptr; 
    }

    const std::type_info& type(){
        return (empty() == true) ? typeid(void) : storage_->value_type();
    }

    template<typename T> friend T any_cast(Any* a); 

    template<typename T> 
    T get_value() {
        return static_cast<Any::Derived<T>*>(storage_)->value_;
    }

    friend void swap(Any& a, Any& b){
        std::swap(a.storage_, b.storage_);
    }

private:
    class Base{
    public:
        virtual const std::type_info& value_type() const = 0;
        virtual Base* get_value() = 0;
        virtual ~Base(){}
    };

    template<typename T>    
    class Derived: public Base{
    public:
        Derived(const T& value): value_(value){}

        Derived(T&& value): value_(std::move(value)){
            std::cout << "MOVE" << std::endl;
        }

        Base* get_value() override {
            return new Derived<T>(value_);
        }

        const std::type_info& value_type() const override {
            return typeid(value_);
        }
        T value_;  
    };
    Base* storage_;
};

template<typename T> 
T any_cast(Any* a) {
    if (a->type() != typeid(T)) throw std::runtime_error("bad_any_cast");
    return static_cast<Any::Derived<T>*>(a->storage_)->value_;
}
};
#endif

