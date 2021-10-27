#include <iostream>
#include "hash_table.hpp"
#include <cmath>
#include <exception>
#include <cassert>

void HashTable::free_cells() {
    for (int i = 0; i < capacity_; i++) {
        if (cells[i] != NULL) {
            delete cells[i];
        }
    }
    delete[] cells;
}

void HashTable::print_table() {
   std::cout << "Table" << std::endl;
   for (int i = 0; i < capacity_; i++) {
       if (cells[i]) {
           std::cout << "name: " << cells[i]->value.name << " age: " << cells[i]->value.age << std::endl;
       }
       else {
           std::cout << "There is noting in " << i << std::endl;
       }
   }
   std::cout << std::endl;
}

void HashTable::init_cells(const Cells** cells) {
    for (int i = 0; i < capacity_; i++) {
        cells[i] = nullptr;
    }
}

HashTable::HashTable(int capacity): cells(new const Cells *[MIN_SIZE]), capacity_(capacity) {
    cells = new const Cells * [MIN_SIZE];
    size_ = 0;
    capacity_ = MIN_SIZE;
    init_cells(cells);
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

unsigned int HashTable::calc_hash(const std::string & expression) const {
    int len = expression.length();
    int p = 1;
    unsigned int hash = 0;
    for (int i = 0; i < len; i++) {
        hash = (hash + expression[i] * p) % capacity_;
        p *= PRIME_1;
        if (p > 0)
            p = 1;
    }
    return hash;
}

HashTable::HashTable(const HashTable& b) {
    cells = new const Cells * [b.capacity_];
    capacity_ = b.capacity_;
    size_ = b.size_;
    init_cells(cells);
    copy_cells(cells, b.cells, b.capacity_);
}

HashTable& HashTable::operator=(const HashTable& b) {
    if (this != &b) {
        free_cells();
        size_ = b.size_;
        capacity_ = b.capacity_;
        cells = new Cells * [b.capacity_];
        copy_cells(cells, b.cells, b.capacity_);
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
    // const Cells** a = cells;
    // this->cells = b.cells;
    // b.cells = a;
    std::swap(cells, b.cells);
    std::swap(size_ , b.size_);
    std::swap(capacity_ , b.capacity_);
}

void HashTable::clear() {
    free_cells();
    size_ = 0;
    cells = new const Cells * [capacity_];
    init_cells(cells);
}

void HashTable::rebuld_table(const Cells** array) {
    size_ = 0;
    for (int i = 0; i < capacity_ / 2; i++) {
        if (array[i] != NULL)
            insert(array[i]->key, (array[i]->value));
    }
}

void HashTable::copy_cells(const Cells** to, const Cells** from, int capacity) {
    for (int i = 0; i < capacity; i++) {
        to[i] = NULL;
        if (from[i] != NULL) {
            to[i] = new Cells(from[i]->key, from[i]->value);
        }
    }
}

bool HashTable::resize() {
    const Cells** array = new Cells * [capacity_ * 2];
    if (array == NULL)
        return false;

    init_cells(array);

     size_ = 0;
    for (int i = 0; i < capacity_ / 2; i++) {
        if (array[i] != NULL)
            insert(array[i]->key, (array[i]->value), capacity_ * 2);
    }

    copy_cells(array, cells, capacity_);

    free_cells();
    cells = array;
    capacity_ *= 2;
    init_cells(cells);
    return true;

    // rebuld_table(array); // there are nothing bags

    // for (int i = 0; i < capacity_ / 2; i++) {
    //     if (array[i] != NULL) {
    //         delete array[i];
    //     }
    // }
    // delete[] array;

    // return true;
}

bool HashTable::is_occupied(int pos) {
    if (cells[pos] == NULL) {
        return false;
    }
    return true;
}

bool HashTable::insert(const Key& k, const Value& v, int capacity) {
    if (size_ == capacity_) {
        if (!resize()) {
            assert(false);
        }
    }

    int hash = calc_hash(k);

    while (is_occupied(hash)) {
        hash = (hash + 1) % capacity_;
    }

    size_++;
    cells[hash] = new Cells(k, v);
    if (cells[hash] == NULL)
        std::cout << "hello";
    return true;
}

bool HashTable::insert(const Key& k, const Value& v) {
   return insert(k, v, capacity_);
}

Cells * HashTable::find(const Key & k) {
    int hash = calc_hash(k);
    int temp = hash;
    do {
        if (cells[hash] != NULL && cells[hash]->key == k) {
            return cells[hash];
        }
        hash = (hash + 1) % capacity_;
    } while (temp != hash);
    return nullptr;
}

Value& HashTable::operator[](const Key& k) {
    //find()
    int hash = calc_hash(k);
    if (contains(k)) {
        while (cells[hash] == NULL || cells[hash]->key != k) { // go to first cell with key k
            hash = (hash + 1) % capacity_;
        }
        return (Value&)(cells[hash]->value);
    }
    size_++;
    static Value v("", 0);
    cells[hash] = new Cells(k, v);
    return (Value&)(cells[hash]->value);
}

bool HashTable::contains(const Key& k) const {
    int hash = calc_hash(k);
    int temp = hash;
    do {
        if (cells[hash] != NULL && cells[hash]->key == k) {
            return true;
        }
        hash = (hash + 1) % capacity_;
    } while (temp != hash);

    return false;
}

bool HashTable::erase(const Key& k) {
    Cells * cell = find(k);
    if (cell == nullptr) return false;
    delete cell;
    cell = nullptr;
    size_--;
    return true;

    if (contains(k)) {
        int hash = calc_hash(k);
        while (cells[hash] == NULL || cells[hash]->key != k) {
            hash = (hash + 1) % capacity_;
        }
        delete cells[hash];
        cells[hash] = NULL;
        size_--;
        return true;
    }
    return false;
}

Value& HashTable::at(const Key& k) {
    return const_cast<Value &>(at1(k));
}

const Value& HashTable::at1(const Key& k) const {
    if (contains(k)) {
        int hash = calc_hash(k);
        while (cells[hash] == NULL || cells[hash]->key != k) {
            hash = (hash + 1) % capacity_;
        }
        return (cells[hash]->value);
    }
    throw std::runtime_error("no key found");
}

const Value& HashTable::at(const Key& k) const {
    return at1(k);
}

void print_value(Value& a) {
    std::cout << "name: " << a.name << " age: " << a.age << std::endl;
}

bool operator==(const HashTable& a, const HashTable& b) {
    if (a.size() == 0 && b.size() == 0) {
        return true;
    }
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

        else if (a.cells[i]->value.name != b.cells[i]->value.name || a.cells[i]->value.age != b.cells[i]->value.age || a.cells[i]->key != b.cells[i]->key) {
            return false;
        }
    }
    return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
    return !(a == b); // так можно?
}

bool HashTable::empty() const {
    return size_ == 0;
}