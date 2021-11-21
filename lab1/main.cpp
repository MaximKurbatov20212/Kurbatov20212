#include <iostream>
#include "hash_table.hpp"

int main() {
//rebuild
    HashTable table;
    HashTable table1;
    const Value a("Mark", 10);
    const Value b("Maxim", 15);

    table.insert("a" , a); 
    table.insert("e" , b); 

    table.insert("ds" , b); 
    table.insert("dsf" , a);  

    table.insert("dsaf" , a); 
    table.insert("we" , b); 

    table.insert("rw" , b); 
    table.insert("eq" , a); 

    std::cout << table;
    table.erase("a");
    std::cout << table;
}
