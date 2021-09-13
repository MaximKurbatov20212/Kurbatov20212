class int_array {
 public:
 // default ctor
 // copy ctor 
 // operator = 
 // move ctor
 // move operator
 // dtor
    int_array(int capacity);
    ~int_array();
    void increase();
    void is_full();
    int get_capacity();
    int push_back(int i);
    int at(int i);
    int pop_back();
    int size();
 private:
    int * data_;
    int size_ = 0;
    int capacity_;
};