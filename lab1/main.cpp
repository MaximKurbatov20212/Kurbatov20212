#include <iostream>
#include "hash_table.hpp"

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
    std::cout << 65 % table.capacity() << std::endl;
    std::cout << table.contains("A") << std::endl;
    std::cout << table["ds"].name << std::endl;
    

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