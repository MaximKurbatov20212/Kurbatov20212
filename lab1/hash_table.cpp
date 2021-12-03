#include <iostream>
#include "hash_table.hpp"
#include <exception>
#include <cassert>

std::ostream& operator<<(std::ostream &out, const HashTable& a){
    for (int i = 0; i < a.capacity_; i++) {
        if (a.cells[i] != nullptr) {
            out << "key: " << a.cells[i]->key << " name: " << a.cells[i]->value.name << " age: " << a.cells[i]->value.age << " hash = " << a.calc_hash(a.cells[i]->key) << std::endl;
        }
        else {
            out << "cells[" << i << "] = nullptr" << std::endl;
        }

    }
    out << std::endl;
    return out;
}

void HashTable::free_cells() {
    for (int i = 0; i < capacity_; i++) {
        if (cells[i] != nullptr) {
            delete cells[i];
        }
    }
    delete[] cells;
}

HashTable::HashTable(const int capacity) : capacity_(capacity < MIN_CAPACITY ? MIN_CAPACITY : capacity), size_(0), cells(new const Cell* [capacity_]()) {
}

HashTable::HashTable(const HashTable& b) : capacity_(b.capacity_), size_(b.size_), cells(new const Cell* [b.capacity_]()) {
    copy_cells(b.cells, cells, b.capacity_);
}

HashTable::~HashTable() {
    free_cells();
}

size_t HashTable::size() const {
    return size_;
}

size_t HashTable::capacity() const {
    return capacity_;
}

unsigned int HashTable::calc_hash(const std::string& expression) const {
    int len = expression.length();
    int p = 1;
    unsigned int hash = 0;
    for (int i = 0; i < len; i++) {
        hash = (hash + expression[i] * p) % capacity_;
        (p * PRIME_1 > 0) ? p *= PRIME_1 : 1;
    }
    return hash;
}

HashTable& HashTable::operator=(const HashTable& b) {
    if (this != &b) {
        if(capacity_ == b.capacity_){
            size_ = b.size_;
            capacity_ = b.capacity_;
            copy_cells(b.cells, cells, b.capacity_);      
            return *this;
        }
        free_cells();
        size_ = b.size_;
        capacity_ = b.capacity_;
        cells = new const Cell * [b.capacity_]();
        copy_cells(b.cells, cells, b.capacity_);          
    }
    return *this;
}

void HashTable::swap(HashTable& b) {
    std::swap(cells, b.cells);
    std::swap(size_, b.size_);
    std::swap(capacity_, b.capacity_);
}

void HashTable::clear() {
    for (int i = 0; i < capacity_; i++) {
        if (cells[i] != nullptr) {
            delete cells[i];
            cells[i] = nullptr;
        }
    }
    size_ = 0;
}

void HashTable::copy_cells(const Cell** from, const Cell** to, int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (from[i] != nullptr) {
            if(to[i] != nullptr){
                delete to[i];
            }
            to[i] = new Cell(from[i]->key, from[i]->value);
        }
    }
}

 bool HashTable::resize() {
    const Cell** array = new const Cell * [capacity_ * 2](); 
    size_ = 0;
    for (int i = 0; i < capacity_ ; i++) {
        if (cells[i] != nullptr) {
            insert(cells[i]->key, cells[i]->value, capacity_ * 2, array); // size_++; will make "insert" 
        }
    }
    free_cells();
    cells = array;
    capacity_ *= 2;
    return true;
}

bool HashTable::insert(const Key& k, const Value& v, int capacity, const Cell** array) {
    if (size_ * 4 >= capacity * 3) { // 75%
        resize();
        array = cells; // after resizing "cells" and we should accept changes
    }
    int hash = calc_hash(k);
    int temp = hash;
    do {
        if (array[hash] == nullptr) {
            const Cell* cell = new const Cell(k, v);
            array[hash] = cell;
            size_++;
            return true ;
        }
        else if (k == array[hash]->key) { 
            const_cast<Key&>(array[hash]->key) = k;
            const_cast<Value&>(array[hash]->value) = v;
            return false;
        }
        hash = (hash + 1) % capacity;

    } while (hash != temp);
    assert(false);
}

bool HashTable::insert(const Key& k, const Value& v) {
    return insert(k, v, capacity_, cells);
}

int HashTable::find(const Key& k) const {    
    int hash = calc_hash(k);
    while(cells[hash] != nullptr){
        if(cells[hash]->key == k) return hash;
        hash = (hash + 1) % capacity_;
    }
    return -1;
}

Value& HashTable::operator[](const Key& k) {
    int index = find(k);
    if (index == -1) {
        int hash = calc_hash(k);
        size_++;
        static Value v("", 0);
        cells[hash] = new Cell(k, v);
        return (Value&)(cells[hash]->value);
    }
    const Cell* cell = cells[index];
    return const_cast<Value&>(cell->value);
}

bool HashTable::contains(const Key& k) const {
    int index = find(k);
    if (index == -1) {
        return false;
    }
    return true;
}

// void HashTable::shift(int& index){
//     int overflow = 0;
//     int free_cell = index;          
//     int dist = 0;
//     index = (index + 1) % capacity_;
//     if(index == 0) overflow += capacity_;

//     while(cells[index] != nullptr){

//         uint hash = calc_hash(cells[index]->key) + overflow;

//         if(overflow == capacity_ && (((hash % capacity_ != (uint)index) && (hash % capacity_ <= free_cell )) || (free_cell == hash % capacity_))){
//             cells[free_cell] = cells[index];
//             cells[index] = nullptr;
//             free_cell = index;
//             overflow = 0;
//         }
//         else if (overflow != capacity_ && (hash % capacity_ != (uint)index) && (hash % capacity_ <= free_cell) || (hash % capacity_ == capacity_ - 1) ){
//             cells[free_cell] = cells[index];
//             cells[index] = nullptr;
//             free_cell = index;
//         }   
//         index = (index + 1) % capacity_;
//         if(index == 0) overflow = capacity_;
//     }
// }


int HashTable::calc_dist(int a, int b){ // Distance between cells
    if (a - b > 0) return  (a - b) ;
    return (capacity_ - (b - a));
}

void HashTable::shift(int& index){
    int free_cell = index;          

    index = (index + 1) % capacity_;

    while(cells[index] != nullptr){
        uint hash = calc_hash(cells[index]->key); 
        
        int dist = calc_dist(index, free_cell);     

        if(hash != (uint)index && calc_dist(index, hash) >= dist){  // The distance to the free cell must be less than the distance to the reference cell.  
            cells[free_cell] = cells[index];
            cells[index] = nullptr;
            free_cell = index;
        }

        index = (index + 1) % capacity_;
    }
}



bool HashTable::erase(const Key& k) {
    int index = find(k);
    if (index == -1) {
        return false;
    }

    delete cells[index];
    cells[index] = nullptr;
    size_--;

    shift(index);
    return true;
}

const Value& HashTable::at(const Key& k) const {
    int index = find(k);
    if (index == -1) {
        throw std::runtime_error("no key found");
    }
    return (cells[index]->value);
}

Value& HashTable::at(const Key& k) {
    int index = find(k);
    if (index == -1) {
        throw std::runtime_error("no key found");
    }
    return const_cast<Value&>(cells[index]->value);
}

bool operator==(const HashTable& a, const HashTable& b) {
    if (a.size_ == 0 && b.size_ == 0) {
        return true;
    }
    if(a.size_ != b.size_) {
        return false;
    }
    for(int i = 0; i < a.capacity_ ; i++){ 
        if((a.cells[i] != nullptr) && (b.find(a.cells[i]->key) == -1)) return false;
    }
    return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
    return !(a == b);
}

bool HashTable::empty() const {
    return size_ == 0;
}