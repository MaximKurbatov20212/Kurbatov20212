#include <iostream>
#include "hash_table.hpp"
#include <cmath>
#include <cassert>

void HashTable::print_table() {
    std::cout << "Table" << std::endl;
    for(int i = 0 ; i < capacity_ ; i++) {
        std::cout << "name: " << array[i].name << " age: " << array[i].age << std::endl;
    }
    std::cout <<  std::endl;
}

HashTable::HashTable() {
    array = new Value[MIN_SIZE];
    for(int i = 0 ; i < MIN_SIZE ; i++) {

        //Value(array[i]); ?
        //array[i].Value("dsaihd" , 10); ?

        array[i].name = "\0";
        array[i].age = 0;
    }

    size_ = 0;
    capacity_ = MIN_SIZE;
    std::cout << "Ctor" << std::endl;
}

HashTable::~HashTable() {
    std::cout << "Dtor" << std::endl;
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
    // проблема взаимнопростых чисел
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

    //rebuild_table(); добавлю
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
    hash = calc_extra_hash(k); // Знаю, что нельзя
    while (true) {
        if(!is_occupied(hash)) {
            array[hash] = v;
            size_++;
            break;
        }
    }
}

Value& HashTable::operator[](const Key& k) {
    int step = calc_extra_hash(k);
    int hash = calc_main_hash(k);
    for (int i = hash ; ; i += step ) {
        if (array[i].name == k) {
            return array[i];        
        }
    }
}
bool HashTable::erase(const Key& k) {
        // все или только один key?
        // at - аналогично
}

void print_value(Value& a) {
    std::cout << "name: " << a.name << " age: "<< a.age << std::endl;
}

bool operator==(const HashTable& a, const HashTable& b) {
    if (a.size() != b.size()) {
        return false;
    }

    else if (a.capacity() != b.capacity()){
        return false;
    }

    for(int i = 0 ; i < a.capacity_ ; i++){
        if (a.array[i].name != b.array[i].name || a.array[i].age != b.array[i].age){
                return false;
        }
    }
    return true;
}

bool operator!=(const HashTable& a, const HashTable& b) {
    return !(a == b); // так можно?
}

bool HashTable::empty() const{
    if (size_ == 0) {
        return true;
    }
    return false;    
}

int main(){
    HashTable table;
    HashTable b;
    //table.print_table();

    const Value t3 ("John" , 10);
    const Value t4 ("John" , 20);
    const Value t1 ("Menson" , 17);
    const Value t2 ("Alex" , 28);

    table.insert(t3.name , t3);
    table.insert(t4.name , t4);

    table.insert(t1.name , t1);
    table.insert(t2.name , t2);
    
    b.insert(t3.name , t3);
    b.insert(t4.name , t4);

    b.insert(t1.name , t1);
    b.insert(t2.name , t2);
    std::cout << (b == table) << std::endl; 
    
    table.print_table();
    b.print_table();
    return 0;
}