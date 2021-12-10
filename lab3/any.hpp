#ifndef ANY
#define ANY

#include <iostream>
#include <typeinfo>

class Any {
public:
    Any();
    template<typename T>
    static T& get(){
        return value_;
    }
    
    template<typename T> Any(const T& value); //+

    template<typename T> Any(T&& value);   //+

    ~Any();  //+
 
    void operator=(Any& other); //+

    template<typename T> void operator=(T& value);

    template<typename T> T any_cast(Any* a);

    friend void swap(Any& a, Any& b);//+

    friend std::ostream& operator<<(std::ostream &out, Any& a);//+

private:
    class A{
    public:
        virtual void print_info() = 0;
        virtual A* get_value() = 0;
        virtual ~A(){}
    };

    template<typename T>    
    class B: public A{
    public:
        B(const T& value): value_(value){}
        
        A* get_value() override{ return new B<T>(value_);}
        
        static B& get_B(){
            return get_value();
        }

        void print_info() override {
            std::cout << typeid(value_).name() << " " << value_ << std::endl;
        }
    private:
        T value_;    
    };

    class A* storage_;
};

#endif
