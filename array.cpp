#include "array.hpp"
#include <cassert>
#include <iostream>

//int_array::int_array(int capacity): data_(new int[capacity]), capacity_(capacity) {
//}

int_array::int_array(int capacity)  {
    data_ = new  int[capacity];
    this -> capacity_ = capacity;
}

int_array::~int_array() {
    delete[] data_;
}

int int_array::get_capacity(){
    return capacity_;
}

void int_array::increase(){
    std::cout << "Size is too large. New capacity = " << capacity_ * 2 << std::endl;

    int *data_1 = new int[(capacity_*= 2) * 2];

    for(int i = 0 ; i < size_ ; i++) // coping data
        data_1[i] = data_[i];

    delete[] data_; // data_ = NULL
    data_ = data_1; 
    delete[] data_1; 
}

void int_array::is_full(){
    if (size_ == capacity_)
        increase();
}

int int_array::push_back(int i) {
    is_full();
    data_[size_] = i;
    size_++;
    return size_;

}

int int_array::at(int i) {
    assert(i < size_ && i >= 0);
    return data_[i];
}

int int_array::pop_back() {
    assert(size_ > 0);
    size_--;
    return data_[size_];
}

int int_array::size() {
    return size_;
}

int main(int argc, char const *argv[]) {
    int_array arr(2);

    arr.push_back(13);
    // 13
    std::cout << arr.at(0) << std::endl;

    arr.push_back(42);
    // 42
    std::cout << arr.at(1) << std::endl;

    // "Not enough memory. New capacity = 4"
    arr.push_back(51);
    // 51
    std::cout << arr.at(2) << std::endl;

    arr.push_back(2);
    // 2
    std::cout << arr.at(3) << std::endl;

    // "Not enough memory. New capacity = 8"
    arr.push_back(7);
    // 7
    std::cout << arr.at(4) << std::endl;

    std::cout << "Size: " << arr.size() << std::endl;
    //std::cout << "Capacity: " << arr.get_capacity() << std::endl;

    return 0;
}
