#include <iostream>
#include "hash_table.hpp"
#include <exception>
#include <cassert>

std::ostream& operator<<(std::ostream &out, const HashTable& a){
    for (int i = 0; i < a.capacity_; i++) {
        if (a.cells[i] != nullptr) {
            out << "key: " << a.cells[i]->key << " name: " << a.cells[i]->value.name << " age: " << a.cells[i]->value.age << std::endl;
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

HashTable::HashTable(int capacity) : capacity_(capacity), size_(0), cells(new const Cell* [capacity_]()) {}

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
            copy_cells(b.cells, cells, b.capacity_);      // 
            //copy_cells(cells, b.cells, b.capacity_);    
            return *this;
        }
        free_cells();
        size_ = b.size_;
        capacity_ = b.capacity_;
        cells = new const Cell * [b.capacity_]();
        copy_cells(b.cells, cells, b.capacity_);          //
        //copy_cells(cells, b.cells, b.capacity_);
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
            //to[i] = nullptr           not necessary
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

int HashTable::find(const Key& k) const {       // after fix we should to check all cells in the block (above and below)
    int hash = calc_hash(k);
    int hash_1 = hash;
    int temp = hash;
    int flag = 0 , flag_1 = 0;
    do {
        // CR: after fix in erase() if we found nullptr we can stop
        if(flag_1 == 0 && cells[hash_1] != nullptr){                  // go up
            if(cells[hash_1]->key == k)   return hash_1;
        }
        else flag_1 = 1;   // cell[hash_1] = nullptr  

        if (flag == 0 && cells[hash] != nullptr ) {                  // go down
            if(cells[hash]->key == k)   return hash;
        }
        else flag = 1;   // cell[hash] = nullptr                             
        
        if(flag == 1 && flag_1 == 1) return -1;   

        hash_1 = (hash_1 - 1 + capacity_) % capacity_;
        hash = (hash + 1) % capacity_; 
    } while (temp != hash );
    
    return  -1;
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

bool HashTable::erase(const Key& k) {
    int index = find(k);
    if (index == -1) {
        return false;
    }
    delete cells[index];
    cells[index] = nullptr;
    size_--;

    int free_cell = index;          
    index = (index + 1) % capacity_;
    
    // CR: not so easy :) there's a chance that we have this scenario:
    // CR: hash("foo") = 1 hash("bar") = 2
    // CR: then we delete "foo" entry. seems to me that after that we won't find "bar", cause it'll be in a first cell.
    // CR: please write a test after that fix
    
    while(cells[index] != nullptr){
        if(calc_hash(cells[index]->key) != (uint)index){
            cells[free_cell] = cells[index];
            cells[index] = nullptr;
            free_cell = index;
        }
        index = (index + 1) % capacity_;
    }
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

bool compare_cells(const HashTable& a, const HashTable& b) {  // for testing "copy_cells"

    for (int i = 0; i < a.capacity_; i++) {
        if ((a.cells[i] == nullptr) && (b.cells[i] == nullptr)) {
            continue;
        }

        else if (((a.cells[i] == nullptr) && (b.cells[i] != nullptr)) || ((b.cells[i] == nullptr) && (a.cells[i] != nullptr))) {
            return false;
        }

        else if (((a.cells[i]->value.name != b.cells[i]->value.name)) || (a.cells[i]->value.age != b.cells[i]->value.age) || (a.cells[i]->key != b.cells[i]->key)) {
            return false;
        }
    }
    return true;
}