#include <iostream>
#include "hash_table.hpp"
#include <cmath>
#include <cassert>

void HashTable::print_table() {
    std::cout << "Table" << std::endl;
    for (int i = 0; i < capacity_; i++) {
        if (cells[i]) {
            std::cout << "name: " << cells[i]->value->name << " age: " << cells[i]->value->age << std::endl;
        }
        else {
            std::cout << "There is noting in " << i << std::endl;
        }
    }
    std::cout << std::endl;
}

void HashTable::init_cells(const Cells** cells) {
    for (int i = 0; i < capacity_; i++) {
        cells[i] = NULL;
    }
}

HashTable::HashTable() {
    //array = (const Value**)calloc(MIN_SIZE , sizeof(Value*));

    cells = new const Cells * [MIN_SIZE];
    size_ = 0;
    capacity_ = MIN_SIZE;
    //std::cout << array;
    init_cells(cells);
    //std::cout << "Ctor" << std::endl;
}

HashTable::~HashTable() {
    //std::cout << "Dtor" << std::endl;
    delete[] cells;
}

size_t HashTable::size() const {
    return size_;
}

size_t HashTable::capacity() const {
    return capacity_;
}

int HashTable::calc_hash(std::string expression) const{
    int len = expression.length();
    int p = 1;
    unsigned int hash;
    for (int i = 0; i < len; i++) {
        hash = (expression[i] * p) % capacity();
        p *= PRIME_1;
    }
    return hash;
}

HashTable::HashTable(const HashTable& b) {
    cells = new const Cells * [b.capacity_];
    std::copy(b.cells, b.cells + b.capacity_, cells);
    capacity_ = b.capacity_;
    size_ = b.size_;
}

HashTable& HashTable::operator=(const HashTable& b) {
    if (this != &b) {
        delete[] cells;
        size_ = b.size_;
        capacity_ = b.capacity_;
        cells = new const Cells * [b.capacity_];
        std::copy(b.cells, b.cells + b.capacity_, cells);
    }
    return *this;
}

void copy(const Value** from, const Value** to, size_t capacity_) {
    for (int i = 0; i < capacity_; i++) {
        if (from[i]) {
            to[i] = new  Value;
            to[i] = from[i];
        }
        else
            to[i] = NULL;
    }
}

void HashTable::swap(HashTable& b) {
    const Cells** a = cells;
    this->cells = b.cells;
    b.cells = a;
}

void HashTable::clear() {
    delete[] this->cells;
    cells = new const Cells * [capacity_];
    init_cells(cells);
}

void HashTable::rebuld_table(const Cells** array) {
    size_ = 0;
    for (int i = 0; i < capacity_ / 2; i++) {
        if (array[i] != NULL)
            insert(array[i]->key, *(array[i]->value));
    }
}

bool HashTable::resize() {
    //std::cout << "resize\n";

    const Cells** array = new const Cells * [capacity_];
    if (array == NULL)
        return false;

    init_cells(array);
    std::copy(cells, cells + capacity_, array);

    delete[] cells;
    capacity_ *= 2;
    cells = new const Cells * [capacity_];
    init_cells(cells);

    rebuld_table(array); // there are nothing bags

    delete[] array;
    return true;
}

bool HashTable::is_occupied(int pos) {
    if (cells[pos] == NULL) {
        cells[pos] = new Cells;
        return false;
    }
    return true;
}

bool HashTable::insert(const Key& k, const Value& v) {
    if (size_ == capacity_) {
        if(!resize()){
            assert(false);
        }
    }
    int hash = calc_hash(k);

    while (is_occupied(hash)) {
        hash = (hash + 1) % capacity_;
    }

    size_++;
    cells[hash] = new const Cells(k, &v);
    return true;
}

Value& HashTable::operator[](const Key& k) {
    if(contains(k)){
        int hash = calc_hash(k);
        while(cells[hash]->key != k){
            hash = (hash + 1) % capacity_;
        }
            return *(Value*)(cells[hash]->value);
    }
    std::cerr << "there is no same key" << std::endl;
    assert(false);
}

bool HashTable::contains(const Key& k) const {
    int hash = calc_hash(k);
    int temp = hash;
    do {
        if(cells[hash] == NULL){
            return false;
        } 
        else if(cells[hash]->key == k) {
            return true;
        }
        hash = (hash + 1) % capacity_;
    } while(temp != hash);

    return false;
}   

bool HashTable::erase(const Key& k) {
    if(contains(k)){
        int hash = calc_hash(k);
        while(cells[hash]->key != k){
            hash = (hash + 1) % capacity_;
        }
        delete cells[hash];
        size_--;
        return true;
    }
    return false;
}

Value& HashTable::at(const Key& k){
    int hash = calc_hash(k);

    if (contains(k)){
        while(cells[hash]->key != k){
            hash = (hash + 1) % capacity_;
        }
        return *(Value*)(cells[hash]->value);
    }
    
    cells[hash] = new Cells(k , NULL);
    return *(Value*)(cells[hash]->value);
}

const Value& HashTable::at(const Key& k) const{
    int hash = calc_hash(k);

    if (contains(k)){
        while(cells[hash]->key != k){
            hash = (hash + 1) % capacity_;
        }
        return *(cells[hash]->value);
    }
    
    cells[hash] = new Cells(k , NULL);
    return *(cells[hash]->value);
}


void print_value(Value& a) {
    std::cout << "name: " << a.name << " age: " << a.age << std::endl;
}

bool operator==(const HashTable& a, const HashTable& b) {
    if (a.size() != b.size() || a.capacity() != b.capacity()) {
        return false;
    }

    for (int i = 0; i < a.capacity_; i++) {
        if (a.cells[i] == NULL && b.cells[i] == NULL) {
            continue;
        }

        else if (a.cells[i] == NULL && b.cells[i] != NULL || b.cells[i] == NULL && a.cells[i] != NULL) {
            return false;
        }

        else if (a.cells[i]->value != b.cells[i]->value || a.cells[i]->key != b.cells[i]->key) {
            return false;
        }
    }
    return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
    return !(a == b); // так можно?
}

bool HashTable::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}
