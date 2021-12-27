#ifndef ANY
#define ANY

#include <iostream>
#include <utility>
#include <typeinfo>
#include <cassert>

namespace utils{
class Any {
public:
    // Effects: Makes a instance with void value
    // Throws:  Nothing
    Any(): storage_(nullptr){
          std::cout << "Default Ctor Any" << std::endl;
    }

    // Effects: Makes a copy of value, so that the initial content of the new instance is equivalent in both type and value to value.
    // Throws:  Nothing
    template<typename T>
    Any(T& value): storage_(new Derived<T>(value))  {
        std::cout << "CopyCtor Any" << std::endl;
    }

    // Effects: Forwards value, so that the initial content of the new instance is equivalent in both type and value to value before the forward.
    // Throws:  Nothing
    template<typename T>
    Any(T&& value){
        std::cout << "MoveCtor Any" << std::endl;
        storage_ = new Derived<T>(std::move(value));   
    }

    // Effect: Releases any and all resources used in management of instance.
    // Throws: Nothing
    ~Any(){
        std::cout << "Dtor Any" << std::endl;
        if (storage_ != nullptr) delete storage_;
    } 

    // Effects: Copies content of other into current instance, discarding previous content, so that the new content is equivalent in both type and value to the content of other, or empty if other is empty.
    // Throws:  Nothing
    void operator=(Any& other){
        if (storage_ != nullptr) delete storage_;
        storage_ = other.storage_->get_value();
    }
    
    // Effects: Makes a copy of value, discarding previous content, so that the new content of is equivalent in both type and value to value.
    // Throws:  Nothing
    template<typename T>
    void operator=(T& value){
        if (storage_ != nullptr) delete storage_;
        storage_ = new Derived<T>(value);
    }

    // Returns: true if instance is empty, otherwise false.
    // Throws:  Nothing
    bool empty() const { 
        return storage_ == nullptr; 
    }

    // Returns: The typeid of the contained value if instance is non-empty, otherwise typeid(void).
    const std::type_info& type(){
        return (empty() == true) ? typeid(void) : storage_->value_type();
    }

    // Returns: If passed a pointer, it returns a similarly qualified pointer to the value content if successful, otherwise null is returned. 
    //          If T is ValueType, it returns a copy of the held value, otherwise, 
    //          if T is a reference to (possibly const qualified) ValueType, it returns a reference to the held value.
    // Throws:  May throws std::runtime_erorr("bad_any_cast") if cast is unsuccessful.
    template<typename T> friend T any_cast(Any* a); 

    // Returns: Copy of contained value if instance is non-empty, otherwise typeid(void).
    // Throws:  May throws std::runtime_erorr("bad_any_cast") if cast is unsuccessful but this method will be removed after testing
    template<typename T> 
    T get_value() {
        return static_cast<Derived<T>*>(storage_)->value_;
    }

    // Effects: Exchange of the contents of a and b.
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
}
#endif