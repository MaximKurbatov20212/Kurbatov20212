#ifndef ANY
#define ANY

#include <iostream>
#include <utility>
#include <typeinfo>

namespace utils{
class Any {
public:
    template<typename T>
    Any(const T& value): storage_(new Derived<T>(value))  {
        std::cout << "CopyCtor Any" << std::endl;
    }
    
    template<typename T>
    Any(T&& value): storage_(std::move(new Derived<T>(value))){
        std::cout << "CopyCtor Any Move" << std::endl;
    }       

    ~Any(){
        std::cout << "Dtor Any" << std::endl;
        if (storage_ != nullptr) delete storage_;
    } 

    void operator=(Any& other){
        std::cout << "op=" << std::endl;
        if (storage_ == nullptr) delete storage_;
        storage_ = other.storage_->get_value();
    }

    template<typename T>
    void operator=(T& value){
        if (storage_ == nullptr) delete storage_;
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
        Base* get_value() override {
            return new Derived<T>(value_);
        }
        // Returns type
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