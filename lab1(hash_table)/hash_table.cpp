#include <iostream>
#include "hash_table.hpp"
#include <cmath>
#include <cassert>

void HashTable::print_table() {
    for(int i = 0 ; i < capacity_ ; i++) {
        std::cout << "name: " << array[i].name << " age: " << array[i].age << std::endl;
    }
}

HashTable::HashTable() {
    array = new Value[MIN_SIZE];

    for(int i = 0 ; i < MIN_SIZE ; i++) {
        array[i].name = "\0";
        array[i].age = 0;
    }

    std::cout << array << std::endl;
    size_ = 0;
    capacity_ = MIN_SIZE;
    std::cout << "Ctor" << std::endl;
}

HashTable::~HashTable() {
    std::cout << "Dtor" << std::endl;
    std::cout << array << std::endl;
    delete [] array;
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
        hash = (expression[i] * p)  % capacity();
        p *= PRIME_1;
    }
    return hash;
}

int HashTable::calc_extra_hash(std::string expression){
    int len = expression.length();
    int p = 1;
    unsigned int hash;
    for (int i = 0 ; i < len ; i++) {
        hash = expression[i]  % capacity();
        p *= PRIME_2;
    }
    return (hash != 0) ? hash : 1; // step never is null
}

HashTable::HashTable(const HashTable& b){
    array = new Value[b.capacity_];
    std::copy(b.array , b.array + b.capacity_ , array);
    capacity_ = b.capacity_;
    size_ = b.size_;
}

HashTable& HashTable::operator=(const HashTable& b ) {
    if (this != &b) {
        delete[] array;
        size_ = b.size_;
        capacity_ = b.capacity_;
        array = new Value[b.capacity_];
        std::copy(b.array , b.array + b.capacity_ , array);
    }
    return *this;
}

void HashTable::swap(HashTable& b){
    Value* c = b.array;
    b.array = array;
    array = c;
    std::swap(size_ , b.size_);
    std::swap(capacity_ , b.capacity_);
}

void HashTable::clear() {
    size_ = 0;
    for (int i = 0 ; i < capacity_ ; i++) {
        array[i].name = '\0';
        array[i].age = 0;
    }
}

bool HashTable::resize() {
    Value* array_1 = new Value[capacity_];
    for(int i = 0 ; i < capacity_ ; i++)
        array_1[i] = array[i];
    capacity_ *= 2;
    delete[] array;
    array = array_1;

    //rebuild_table();
}
bool HashTable::is_occupied(int pos) {
    if (array[pos].name == "\0") {
        return false;
    }
    return true;
}

bool HashTable::insert(const Key& k, const Value& v) {
    int hash = calc_main_hash(k);
    if (!is_occupied(hash)){
        array[hash] = v;
        size_++;
        return true;
    }
    while (true) {
        hash = calc_extra_hash(k); // Знаю, что нельзя
        if(!is_occupied(hash)) {
            array[hash] = v;
            size_++;
            break;
        }
    }
}

// Value& HashTable::operator[](const Key& k) {
//     return ;
// }

int main(){
    HashTable table;

    table.print_table();

    const Value v ("John" , 10);
    const Value t ("John" , 20);
    table.insert(v.name , v);
    table.insert(t.name , t);
    table.print_table();
    return 0;
}