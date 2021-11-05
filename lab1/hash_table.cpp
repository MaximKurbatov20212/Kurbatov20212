#include <iostream>
#include "hash_table.hpp"
#include <cmath>
#include <exception>
#include <cassert>


void HashTable::print_table() {
   std::cout << "Table" << std::endl;
   for (int i = 0; i < capacity_; i++) {
       if (cells[i]) {

           std::cout << "name: " << cells[i]->value.name << " age: " << cells[i]->value.age << std::endl;
       }
       else {
           std::cout << "There is nothing in " << i << std::endl;
       }
   }
   std::cout << std::endl;
}

void HashTable::free_cells() {
    for (int i = 0; i < capacity_; i++) {
        if (cells[i] !=  nullptr) {
            delete cells[i];
        }
    }
    delete[] cells;
}


HashTable::HashTable(int capacity): capacity_(capacity), size_(0),cells(new const Cells *[capacity_]) {}

HashTable::HashTable():  capacity_(MIN_SIZE), size_(0), cells(new const Cells *[MIN_SIZE]){}

HashTable::HashTable(const HashTable& b) :  capacity_(b.capacity_) , size_(b.size_) , cells(new const Cells* [b.capacity_]) {
    copy_cells(b.cells, cells, b.capacity_); // from to capacity
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
        copy_cells(cells, b.cells, b.capacity_);
    }
    return *this;
}

void HashTable::swap(HashTable& b) {
    std::swap(cells, b.cells);
    std::swap(size_ , b.size_);
    std::swap(capacity_ , b.capacity_);
}

void HashTable::clear() {
    free_cells();
    size_ = 0;
    capacity_ = 0;
}

void HashTable::copy_cells(const Cells** from, const Cells** to, int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (from[i] !=  nullptr) {
            to[i] = new Cells(from[i]->key, from[i]->value);
        }
    }
}

bool HashTable::resize() {
    const Cells** array = new const Cells * [capacity_ * 2]; // new Cells
    size_ = 0; 
    
    for (int i = 0; i < capacity_ / 2; i++) {
        if (cells[i] !=  nullptr){
            insert(cells[i]->key, (cells[i]->value));
            size_ ++;
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

bool HashTable::insert(const Key& k, const Value& v) {
    if (size_ * 4 > capacity_ * 3) { // 75%
        resize();
    }
    int first_deleted = -1;
    int hash = calc_hash(k);
    int temp = hash;
    do{
        if(is_occupied(hash) && (k == cells[hash]->key)){ // couple equal key
            delete cells[hash];
            const Cells* cell = new const Cells(k , v);   
            cells[hash] = cell;
            return false;
        }
        if(!is_occupied(hash)) { 
            first_deleted = hash;
        }
        hash = (hash + 1) % capacity_;
        
    }while(hash != temp);

    const_cast<Value&>(cells[first_deleted]->value).name = v.name;
    const_cast<Cells*>(cells[first_deleted])->key = k;
    return true;
}


const HashTable::Cells* HashTable::find(const Key & k) const {
    int hash = calc_hash(k);
    int temp = hash;
    do {
        if (cells[hash] !=  nullptr && cells[hash]->key == k) {
            return cells[hash];
        }
        hash = (hash + 1) % capacity_;
    } while (temp != hash);
    return  nullptr;
}

Value& HashTable::operator[](const Key& k) {
    const Cells* cell = find(k);
    if(cell != nullptr){
        return const_cast<Value &>(cell->value);
    }
    int hash = calc_hash(k);
    size_++;
    static Value v("", 0);
    cells[hash] = new Cells(k, v);
    return (Value&)(cells[hash]->value);
}

bool HashTable::contains(const Key& k) const {
    return (find(k) != nullptr);
}

bool HashTable::erase(const Key& k) {
    const Cells * cell = find(k);
    if (cell == nullptr) return false;
    delete cell;
    size_--;
    return true;
}

const Value& HashTable::at(const Key& k) const {
    const Cells* cell = find(k);
    if (cell != nullptr){
        return cell->value;
    }
    throw std::runtime_error("no key found");
}

Value& HashTable::at(const Key& k) {
    return const_cast<Value &>(at(k));
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
        if ((a.cells[i] == nullptr) && (b.cells[i] == nullptr)) {
            continue;
        }

        else if (((a.cells[i] == nullptr) &&  (b.cells[i] != nullptr) )||  ((b.cells[i] == nullptr) && (a.cells[i] != nullptr))) {
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

int main() {
    HashTable table;
    std::cout << table.size();
}