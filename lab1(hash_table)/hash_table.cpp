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
            std::cout << " There is noting in " << i << std::endl;
        }
    }
    std::cout << std::endl;
}

HashTable::HashTable() {
    //array = (const Value**)calloc(MIN_SIZE , sizeof(Value*));

    cells = new const Cells * [MIN_SIZE];
    //std::cout << array;
    for (int i = 0; i < MIN_SIZE; i++) {
        //std::cout << array[i];
        cells[i] = NULL;
    }
    size_ = 0;
    capacity_ = MIN_SIZE;
    std::cout << "Ctor" << std::endl;
}

HashTable::~HashTable() {
    std::cout << "Dtor" << std::endl;
    delete[] cells;
}

size_t HashTable::size() const {
    return size_;
}

size_t HashTable::capacity() const {
    return capacity_;
}

int HashTable::calc_hash(std::string expression) {
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
    // this->array <-> b.array
    const Cells** a = cells;
    this->cells = b.cells;
    b.cells = a;
}

void HashTable::clear() {
    delete[] this->cells;
    cells = new const Cells * [capacity_];
    for (int i = 0; i < capacity_; i++) {
        cells[i] = NULL;
    }
}

// bool HashTable::resize() {
//     Value* array_1 = new Value[capacity_];
//     for(int i = 0 ; i < capacity_ ; i++)
//         array_1[i] = array[i];
//     capacity_ *= 2;
//     delete[] array;
//     array = array_1;

    //rebuild_table(); добавлю
//}

bool HashTable::is_occupied(int pos) {
    if (cells[pos] == NULL) {
        cells[pos] = new Cells;
        return false;
    }
    return true;
}

bool HashTable::insert(const Key& k, const Value& v) {
    size_t hash = calc_hash(k);
    if (!is_occupied(hash)) {
        cells[hash] = new Cells(k, &v);
        return true;
    }
    while (is_occupied(hash)) {
        hash = (hash + 1) % capacity_;
    }
    cells[hash] = new Cells(k, &v);
    return true;
}

// Value& HashTable::operator[](const Key& k) {
//     int step = calc_extra_hash(k);
//     int hash = calc_main_hash(k);
//     for (int i = hash ; ; i += step ) {
//         if (array[i].name == k) {
//             return array[i];        
//         }
//     }
// }
// bool HashTable::erase(const Key& k) {
//         // все или только один key?
//         // at - аналогично
// }

// void print_value(Value& a) {
//     std::cout << "name: " << a.name << " age: "<< a.age << std::endl;
// }

// bool operator==(const HashTable& a, const HashTable& b) {
//     if (a.size() != b.size()) {
//         return false;
//     }

//     else if (a.capacity() != b.capacity()){
//         return false;
//     }

//     for(int i = 0 ; i < a.capacity_ ; i++){
//         if (a.array[i].name != b.array[i].name || a.array[i].age != b.array[i].age){
//                 return false;
//         }
//     }
//     return true;
// }

// bool operator!=(const HashTable& a, const HashTable& b) {
//     return !(a == b); // так можно?
// }

// bool HashTable::empty() const{
//     if (size_ == 0) {
//         return true;
//     }
//     return false;    
// }

int main() {
    HashTable table;
    const Value t("Mark", 10);
    const Value t3("John", 10);
    const Value t2("Alex", 23);
    table.insert("hello", t3);
    table.insert("hello", t2);
    table.insert("hello", t);

    HashTable a;
    const Value t0("Tom", 20);
    const Value t1("Bim", 43);
    a.insert("hello", t1);

    a.insert("fhbs", t0);

    //a.print_table();
    table.print_table();

    // table.swap(a);

    // a.print_table();
    // table.print_table();

    return 0;
}