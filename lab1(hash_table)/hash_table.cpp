#include <iostream>
#include "hash_table.hpp"
#include <cmath>
#include <cassert>

HashTable::HashTable() {
    IntArray array(MIN_BUF); // Массивчик
    std::cout << "CONSTRUCTOR" << std::endl;
}

HashTable::~HashTable() {
    std::cout << "DESTUCTOR" << std::endl;
}

// void HashTable::swap(HashTable& b) {
//     HashTable* c = this;
//     this = &b;
//     b = c;
// }


int calc_main_hash(std::string expression){
    int len = expression.length();
    for (int i = 0 ; i < len ; i++) {
        size_t hash = expression[i] * pow(3.0 , 1.0);
    }
    return len;
}

int HashTable::calc_extra_hash(std::string expression){
    return 1;
}


IntArray::IntArray(int capacity): array_(new int[capacity]), capacity_(capacity) {
    std::cout << "Ctor_array" << std::endl;
}

IntArray::~IntArray() {
    std::cout << "Dtor_array" << std::endl;
    delete[] array_;
}

void IntArray::resize(){
    int* arr = new int[size_ * 2];
    capacity_ = capacity_ * 2;
    for (int i = 0; i < size_; i++){
        arr[i] = array_[i];
    }
    delete [] array_;
    array_ = arr;
}

int IntArray::push_back(int i) {
    if (size_ + 1 == capacity_) resize();
    array_[size_] = i;
    size_++;
    return size_;
}

int IntArray::at(int i) {
    assert(i < size_ && i >= 0);
    return array_[i];
}

int IntArray::pop_back() {
    assert(size_ > 0);
    size_--;
    return array_[size_];
}

int IntArray::size() {
    return size_;
}

int main(){
    HashTable table;

    return 0;
}