#ifndef ANY
#define ANY

#include <iostream>
#include <utility>
#include <typeinfo>
#include <cassert>

namespace utils{

class any_cast_error : public std::runtime_error {
public:
    explicit any_cast_error(): std::runtime_error("any_cast_error"){};
};

class Any {
public:
    // Effects: Makes an instance with void value
    // Throws:  Nothing
    Any()= default;


    // Effects: Makes a copy of other's value, so that the initial content of the new instance is equivalent in both type and value to value.
    // Throws:  Nothing
    Any(Any& other): storage_(other.storage_->get_value()) {}


    // Effects: Makes a copy of value, so that the initial content of the new instance is equivalent in both type and value to value.
    // Throws:  Nothing
    template<typename T>
    Any(T& value): storage_(new Derived<T>(value)) {}


    // Effects: Forwards value, so that the initial content of the new instance is equivalent in both type and value to value before the forward.
    // Throws:  Nothing
    template<typename T>
    Any(T&& value): storage_(new Derived<T>(std::move(value))){}


    // Effect: Releases any and all resources used in management of instance.
    // Throws: Nothing
    ~Any(){
        delete storage_;
    } 


    // Effects: Copies content of other into current instance, discarding previous content, so that the new content is equivalent in both type and value to the content of other, or empty if other is empty.
    // Throws:  Nothing
    Any& operator=(Any& other){
        if(this != &other){
            delete storage_;
            storage_ = other.storage_->get_value();
        }
        return *this;
    }


    // Effects: Makes a copy of value, discarding previous content, so that the new content of is equivalent in both type and value to value.
    // Throws:  Nothing
    template<typename T>
    Any& operator=(T& value){
        delete storage_;
        storage_ = new Derived<T>(value);
        return *this;
    }


    // Returns: true if instance is empty, otherwise false.
    // Throws:  Nothing
    bool empty() const { 
        return storage_ == nullptr; 
    }


    // Returns: If passed a pointer, it returns a similarly qualified pointer to the value content if successful, otherwise null is returned. 
    //          If T is ValueType, it returns a copy of the held value, otherwise, 
    //          if T is a reference to (possibly const qualified) ValueType, it returns a reference to the held value.
    // Throws:  May throws "any_cast_error" if cast is unsuccessful.
    template<typename T> friend T any_cast(Any* a); 


    // Effects: Exchange of the contents of a and b.
    friend void swap(Any& a, Any& b){
        std::swap(a.storage_, b.storage_);
    }

private:
    class Base{
    public:
        virtual Base* get_value() = 0;
        virtual ~Base()= default;
    };

    template<typename T>    
    class Derived: public Base{
    public:
        explicit Derived(const T& value): value_(value){}

        explicit Derived(T&& value): value_(std::move(value)){}

        Base* get_value() override {
            return new Derived<T>(value_);
        }
        T value_;  
    };

    Base* storage_{nullptr};
};

template<typename T> 
T any_cast(Any* a) {
    auto * derived = dynamic_cast<Any::Derived<T>*>(a->storage_);
    if (derived == nullptr) throw any_cast_error();
    // CR: probably here copy ctor is called? not sure, please check
    
    // if we will not call copy ctor then we will have such a problem how two variables will manage the same piece of memory
    // and user can doing something(free pointer or just change value indirectly)
    // is it right?
    return derived->value_;
    }
}
#endif