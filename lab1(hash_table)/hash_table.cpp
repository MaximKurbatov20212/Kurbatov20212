#include <iostream>
#include "hash_table.hpp"
#include <cmath>
#include <cassert>

HashTable::HashTable() {
    int* array = new int(MIN_BUF);
    size_ = 0;
    capacity_ = MIN_BUF;
    std::cout << "Ctor" << std::endl;
}

HashTable::~HashTable() {
    std::cout << "Dtor" << std::endl;
    delete[] array;
}

size_t HashTable::size() const{
    return size_;
}

size_t HashTable::capacity() const{
    return capacity_;
}

int HashTable::calc_main_hash(std::string expression){
    int len = expression.length();
    int p = 1;
    unsigned int hash;
    for (int i = 0 ; i < len ; i++) {
        hash = expression[i] * p;
        p *= 7;
    }
    return hash % capacity();
}

int HashTable::calc_extra_hash(std::string expression){
    int len = expression.length();
    int p = 1;
    unsigned int hash;
    for (int i = 0 ; i < len ; i++) {
        hash = expression[i] * p;
        p *= 11;
    }
    return hash % capacity();
}

HashTable::HashTable(const HashTable& b){
    array = new int[b.capacity_];
    std::copy(b.array , b.array + b.capacity_ , array);
    capacity_ = b.capacity_;
    size_ = b.size_;
}

HashTable& HashTable::operator=(const HashTable& b ) {
    if (this != &b) {
        delete[] this->array;
        size_ = b.size_;
        capacity_ = b.capacity_;
        array = new int(b.capacity_);
        std::copy(b.array , b.array + b.capacity_ , array);
    }
    return *this;
}

void HashTable::swap(HashTable& b){
    // HashTable& a = b; ???
    // &b = this;
    // this = &a;
    int* a = b.array;
    int s = b.size_;
    int c = b.capacity_;
    b.array = array;
    b.size_ = size_;
    b.capacity_ = capacity_;
    array = a;
    capacity_ = c;
    size_ = s;
}
void HashTable::clear() {
    size_ = 0;
    for (int i = 0 ; i < capacity_ ; i++) {
        array[i] = 0;
    }
}


int main(){
    HashTable table;
    std::cout <<  table.calc_main_hash("dasd") << std::endl;
    std::cout <<  table.calc_extra_hash("dasd") << std::endl;
    return 0;
}