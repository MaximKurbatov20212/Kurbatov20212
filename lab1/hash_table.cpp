#include <iostream>
#include "hash_table.hpp"
#include <exception>

void HashTable::print_table() {
    for (int i = 0; i < capacity_; i++) {
        if (cells[i] != nullptr) {

            std::cout << "key: " << cells[i]->key << "name: " << cells[i]->value.name << " age: " << cells[i]->value.age << std::endl;
        }
        else {
            std::cout << "cells[" << i << "] = nullptr" <<  std::endl;
        }
    }
    std::cout << std::endl;
}

void HashTable::init_cells() {
    for (int i = 0; i < capacity_; i++) {
        cells[i] = nullptr;
    }
}

void HashTable::free_cells() {
    for (int i = 0; i < capacity_; i++) {
        if (cells[i] != nullptr) {
            delete cells[i];
            cells[i] = nullptr;
        }
    }
    delete[] cells;
    cells = nullptr;
}


HashTable::HashTable(int capacity) : capacity_(capacity), cells(new const Cells* [capacity_]), size_(0) {
    init_cells();
}

HashTable::HashTable() : capacity_(MIN_SIZE), cells(new const Cells* [MIN_SIZE]), size_(0) {
    init_cells();
}

HashTable::HashTable(const HashTable& b) : capacity_(b.capacity_), size_(b.size_), cells(new const Cells* [b.capacity_]) {
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

unsigned int HashTable::calc_hash(const std::string expression) const {
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
        free_cells();
        size_ = b.size_;
        capacity_ = b.capacity_;
        cells = new const Cells * [b.capacity_];
        init_cells();
        copy_cells(cells, b.cells, b.capacity_);
    }
    return *this;
}

void HashTable::swap(HashTable& b) {
    std::swap(cells, b.cells);
    std::swap(size_, b.size_);
    std::swap(capacity_, b.capacity_);
}

void HashTable::clear() {
    free_cells();
    size_ = 0;
    capacity_ = 0;
}

void HashTable::copy_cells(const Cells** from, const Cells** to, int capacity) {
    for (int i = 0; i < capacity; i++) {
        to[i] = nullptr;
        if (from[i] != nullptr) {
            to[i] = new Cells(from[i]->key, from[i]->value);
        }
    }
}

bool HashTable::resize() {
    const Cells** array = new const Cells * [capacity_ * 2]; // new Cells
    for (int i = 0; i < capacity_ * 2; i++) {
        array[i] = nullptr;
    }

    size_ = 0;
    for (int i = 0; i < capacity_ / 2; i++) {
        if (cells[i] != nullptr) {
            insert(cells[i]->key, cells[i]->value, capacity_ * 2, array);
            size_++;
        }
    }

    free_cells();
    delete[] cells;
    cells = array;
    capacity_ *= 2;
    return true;
}

bool HashTable::is_occupied(int pos) {
    return (cells[pos] != nullptr);
}

bool HashTable::insert(const Key& k, const Value& v, int capacity, const Cells** array) {
    if (size_ * 4 > capacity * 3) { // 75%
        resize();
    }
    int hash = calc_hash(k);
    int temp = hash;
    do {
        if (is_occupied(hash) && (k == array[hash]->key)) { // couple equal key
            delete array[hash];
            const Cells* cell = new const Cells(k, v);
            array[hash] = cell;
            return false;
        }
        if (!is_occupied(hash)) {
            const Cells* cell = new const Cells(k, v);
            array[hash] = cell;
            size_++;
            break;
        }
        hash = (hash + 1) % capacity;

    } while (hash != temp);

    const_cast<Value&>(array[hash]->value) = v;
    const_cast<Cells*>(array[hash])->key = k;
    return true;
}

bool HashTable::insert(const Key& k, const Value& v) {
    return insert(k, v, capacity_, cells);
}

int HashTable::find(const Key& k) const {
    int hash = calc_hash(k);
    int temp = hash;
    do {
        if (cells[hash] != nullptr && cells[hash]->key == k) {
            return hash;
        }
        hash = (hash + 1) % capacity_;
    } while (temp != hash);
    return  0;
}

Value& HashTable::operator[](const Key& k) {
    const Cells* cell = cells[find(k)];
    if (cell != nullptr) {
        return const_cast<Value&>(cell->value);
    }
    int hash = calc_hash(k);
    size_++;
    static Value v("", 0);
    cells[hash] = new Cells(k, v);
    return (Value&)(cells[hash]->value);
}

bool HashTable::contains(const Key& k) const {
    return (cells[find(k)] != nullptr);
}

bool HashTable::erase(const Key& k) {
    int index = find(k);
    if (cells[index] == nullptr) return false;
    delete cells[index];
    cells[index] = nullptr;
    size_--;
    return true;
}

const Value& HashTable::at(const Key& k) const {
    int index = find(k);
    if (cells[index] != nullptr) {
        return cells[index]->value;
    }
    throw std::runtime_error("no key found");
}

Value& HashTable::at(const Key& k) {
    int index = find(k);
    if (cells[index] != nullptr) {
        return const_cast<Value&>(cells[index]->value);
    }
    throw std::runtime_error("no key found");

    //return const_cast<Value&>(at(k)); calls itself    
}

bool operator==(const HashTable& a, const HashTable& b) {
    if (a.size() == 0 && b.size() == 0) {
        return true;
    }
    if (a.size() != b.size() || a.capacity() != b.capacity()) {
        return false;
    }

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

bool operator!=(const HashTable& a, const HashTable& b) {
    return !(a == b);
}

bool HashTable::empty() const {
    return size_ == 0;
}
