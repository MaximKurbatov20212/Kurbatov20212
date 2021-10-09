#define NDEBUG
#include <iostream>
#include "hash_table.hpp"
#include <cmath>
#include <cassert>

void HashTable::print_table() {
    std::cout << "\nTable: " << std::endl;
    for (int i = 0; i < capacity_; i++) {
        if (cells[i]) {
            std::cout << "name: " << cells[i]->value->name << " age: " << cells[i]->value->age << std::endl;
        }
        else {
            std::cout << "---------------" << std::endl;
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

int HashTable::calc_hash(const Key& expression) {
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
    std::cout << "resize\n";

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
        resize();
    }
    size_t hash = calc_hash(k);

    if (!is_occupied(hash)) {
        cells[hash] = new const Cells(k, &v);
        size_++;
        return true;
    }
    while (is_occupied(hash)) {
        hash = (hash + 1) % capacity_;
    }
    size_++;
    cells[hash] = new const Cells(k, &v);
    return true;
}

Value& HashTable::operator[](const Key& k) {
    int hash = calc_hash(k);
    int temp = hash;
    while (!is_occupied(hash)) {
        hash = (hash + 1) % capacity_;
        if (temp == hash) { // прошли цикл
            while (!is_occupied(hash)){
                if(!is_occupied(hash)){
                    cells[hash] = new const Cells(k , NULL);
                    return *(Value*)(cells[hash]->value);
                }
                hash = (hash + 1) % capacity_;
                
            }
        }
    }
    return *(Value*)(cells[hash]->value);
}

bool HashTable::erase(const Key& k) {
    int hash = calc_hash(k);
    int temp = hash;
    while(true) {
        if(cells[hash] != NULL && cells[hash]->key == k) {
            delete cells[hash];
            cells[hash] = NULL;
            size_--;
            return true;
        }
        hash = (hash + 1) % capacity_;
        if(hash == temp)
            return false;// прошли цикл
    }
}

Value& HashTable::at(const Key&k){
    int hash = calc_hash(k);
    int temp = hash;
    while(true){
        if(hash == temp){
            std::cout << "there is no same key";
            assert(hash == true);
        }
        else if(is_occupied(hash) && cells[hash]->key == k){
            return *((Value*)cells[hash]->value);
        }
        hash = (hash + 1) % capacity_;
    }
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

int main() {
    HashTable table;
    const Value t("Mark", 10);
    const Value t3("John", 10);
    const Value t2("Alex", 23);
    const Value t4("Maxim", 90);
    const Value t5("Sanya", 21);
    table.insert("hello", t3);
    table.insert("hello", t2);
    table.insert("hello", t);
    table.insert("dsa", t4);
    table.insert("fsas", t5);
    table.print_table();
    table.at("sa");
    table.erase("qd");
    table.print_table();

    // HashTable a;
    // a.insert("hello", t3);
    // a.insert("hello", t2);
    // a.insert("hello", t);
    // a.insert("dsa" , t);
    // std::cout << (a == table) << std::endl;
    // print_value(a["hello"]);
    // print_value(a["dsa"]);
    //a.print_table();
    //table.print_table();

    // table.swap(a);

    // a.print_table();
    // table.print_table();

    return 0;
}