#include <iostream>
#include "hash_table.hpp"
#include <cmath>
#include <cassert>

void HashTable::print_table() {
    
    std::cout << "Table" << std::endl;
    for(int i = 0 ; i < capacity_ ; i++) {
        if (array[i]){
            std::cout << "name: " << array[i]->name << " age: " << array[i]->age << std::endl;
        }
        else    {
            std::cout << " There is noting in " << i << std::endl;    
        }
    }
    std::cout <<  std::endl;
}

HashTable::HashTable() {
    //array = (const Value**)calloc(MIN_SIZE , sizeof(Value*));

    array = new const Value*[MIN_SIZE];
    std::cout << array;
    for(int i = 0 ; i < MIN_SIZE ; i++) {
       //std::cout << array[i];
       array[i] = NULL;
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

int HashTable::calc_hash(std::string expression){
    int len = expression.length();
    int p = 1;
    unsigned int hash;
    for (int i = 0 ; i < len ; i++) {
        hash = (expression[i] * p)  % capacity();
        p *= PRIME_1;
    }
    return hash;
}

HashTable::HashTable(const HashTable& b){
    array = new const Value*[b.capacity_];
    std::copy(b.array , b.array + b.capacity_ , array);
    capacity_ = b.capacity_;
    size_ = b.size_;
}

HashTable& HashTable::operator=(const HashTable& b ) {
    if (this != &b) {
        delete[] array;
        size_ = b.size_;
        capacity_ = b.capacity_;
        array = new const Value*[b.capacity_];
        std::copy(b.array , b.array + b.capacity_ , array);
    }
    return *this;
}

void HashTable::swap(HashTable& b){
    // this->array <-> b.array
    const Value** a = array;
    this->array = b.array;
    b.array = a;
}

void HashTable::clear() {
    delete[] array;
    array = new const Value*[capacity_];
    for(int i = 0 ; i < capacity_ ; i++) {
        array[i] = NULL;
    }
}

void copy(const Value** from , const Value** to , size_t capacity_){
    for (int i = 0; i < capacity_; i++) {
        if (from[i]) {
            to[i] = new  Value;
            to[i] = from[i];
        }
        else
            to[i] = NULL;
    }
}

bool HashTable::resize() {
    const Value** array_1 = new const Value*[capacity_];
    if(!array_1) {
        return false;
    }
    copy(array , array_1 , capacity_);
    delete array;
    capacity_ *= 2;
    array = array_1;
    //rebuild_table(); добавлю
}

bool HashTable::is_occupied(int pos) {
    if(array[pos] == NULL) {
        array[pos] = new Value();
        return false;
    }
    return true;
}

bool HashTable::insert(const Key& k, const Value& v) {
    if(size_ == capacity_) {
        if(!resize()){
            std::cout << "no memory" << std::endl;
        }
    }
    size_t hash = calc_hash(k);
    while(is_occupied(hash)) {
        hash = (hash + 1) % capacity_;
    }
    array[hash]->key = k;
    array[hash]->name = v.name;
    array[hash]->age = v.age;
    
    size_++;
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

bool operator==(const HashTable& a, const HashTable& b) {
    if (a.size() != b.size()) {
        return false;
    }

    else if (a.capacity() != b.capacity()){
        return false;
    }

    for(int i = 0 ; i < a.capacity_ ; i++){
        if(a.array[i] == NULL && b.array[i] != NULL || a.array[i] != NULL && b.array[i] == NULL) {
            return false;
        }
        if(a.array[i] == NULL && b.array[i] == NULL){
            continue;
        }    
        if (a.array[i]->name != b.array[i]->name || a.array[i]->age != b.array[i]->age){
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
    const Value t3 ("John" , 10);
    const Value t2 ("Alex" , 23);
    const Value t4 ("Sanya"  , 19);
    table.insert("hello" , t3);
    table.insert("fhbs" , t2);
    table.insert("dsa" , t4);

    HashTable a;
    const Value t0 ("John" , 10);
    const Value t1 ("ALex" , 23);
    a.insert("hello" , t0);
    a.insert("fhbs" , t1);

    a.print_table();
    table.print_table();
    std::cout << (a == table) << std::endl;
    table.clear();
    table.print_table();

    // table.swap(a);

    // a.print_table();
    // table.print_table();

    return 0;
}