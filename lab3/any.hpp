#pragma once
#include <iostream>

class Any {
public:
    Any(){
        std::cout << "Standard Ctor" << std::endl;  
    }
    
    template<typename T>
    Any(const T& value): storage_(new Derived<T>(value))  {
        std::cout << "CopyCtor Any" << std::endl;
    }   

    template<typename T>
    Any(T&& value){
        std::cout << "CopyCtor Any Move" << std::endl;
        Derived<T>* tmp = dynamic_cast<Derived<T>*>(storage_);
        tmp = std::move(new Derived<T>(value));       
    }       

    ~Any(){
        delete storage_;
        std::cout << "Dtor Any" << std::endl;
    } 

    void operator=(Any& other){
        std::cout << "op=" << std::endl;
        if (storage_ == nullptr) delete storage_;
        storage_ = other.storage_->get_value();
    }

    template<typename T>
    void operator=(T& value){
        if (storage_ == nullptr) delete storage_;
        storage_(std::move(value));
    }

    template<typename T> 
    friend T any_cast(Any* a){  
        try{ 
            Derived<T>* tmp = dynamic_cast<Derived<T>*>(a->storage_);
            return static_cast<T>(tmp->value_);
        }
        catch(std::exception& e){
            throw std::runtime_error("bad_any_cast");
        }
    }        

private:
    class Base{
    public:
        virtual Base* get_value() = 0;
        virtual ~Base(){}
    };

    template<typename T>    
    class Derived: public Base{
    public:
        Derived(const T& value): value_(value){}
        Base* get_value() override {return new Derived<T>(value_);}
        T value_;  
    };
    Base* storage_;
};