#include <gtest/gtest.h>
#include "hash_table.hpp"
#include <ctime>
#include <unistd.h>
#include <limits.h>

bool compare(const Value& a , const Value& b ){
    if (a.name == b.name && a.age == b.age)
        return true;
    return false;      
}

// random string
std::string gen_str(const int len) {
    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    srand( (unsigned) time(NULL) * getpid());

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) 
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    
    return tmp_s;
}

//rebuild
TEST(test_table , resize){
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Maxim", 15);
    const Value c("Alex", 13);
    const Value d("Ivan", 321);

    EXPECT_EQ(table.size() , 0);
    EXPECT_EQ(table.capacity() , 4);

    table.insert("qwerty" , a); //capacity = 4, size = 1 
    EXPECT_EQ(table.size() , 1);
    EXPECT_EQ(table.capacity() , 4);

    table.insert("q" , b); //capacity = 4, size = 2
    EXPECT_EQ(table.size() , 2);
    EXPECT_EQ(table.capacity() , 4);

    table.insert("qw" , c); //capacity = 4, size = 3
    EXPECT_EQ(table.size() , 3);
    EXPECT_EQ(table.capacity() , 4);

    table.insert("qwer" , d); //capacity = 8, size = 4
    EXPECT_EQ(table.size() , 4);
    EXPECT_EQ(table.capacity() , 8);

    table.insert("safs" , d); //capacity = 8, size = 5
    EXPECT_EQ(table.size() , 5);
    EXPECT_EQ(table.capacity() , 8);

    table.insert("sasaklfnkfs" , d); //capacity = 8, size = 6
    EXPECT_EQ(table.size() , 6);
    EXPECT_EQ(table.capacity() , 8);

    table.insert("ssanjkdnaf" , d); //capacity = 16, size = 7
    EXPECT_EQ(table.size() , 7);
    EXPECT_EQ(table.capacity() , 16);

    table.clear();
    EXPECT_EQ(table.size() , 0);
    EXPECT_EQ(table.capacity() , 16);
}


TEST(test_table , at_cell_and_compare){ //NEW TEST
    HashTable table;
    const Value a("", 0);
    table.insert("foo" , a);
    const Value b = table.at("foo");
    EXPECT_TRUE(b.name == a.name);
}

//insert
TEST(test_table , initial_size_is_zero) {
    HashTable table;
    EXPECT_EQ(table.size() , 0);
}

TEST(test_table , insert_one_value) { 
    HashTable table;
    const Value t(gen_str(rand() % 20), 21);
    table.insert(gen_str(rand() % 20), t);
    EXPECT_EQ(table.size() , 1);
}

TEST(test_table , insert_two_equal_value_with_equal_keys) { 
    HashTable table;
    std::string str = gen_str(rand() % 20);
    std::string key = gen_str(rand() % 20);
    const Value a(str, 20);
    const Value b(str, 20);
    table.insert(key, a);
    table.insert(key, b);
    EXPECT_EQ(table.size() , 1);
}


TEST(test_table , insert_two_not_equal_value_with_equal_keys) { 
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Maxim", 15);
    table.insert("hello", a);
    table.insert("hello", b);
    EXPECT_EQ(table.size() , 1);
}

//empty
TEST(test_table , is_empty_1) {
    HashTable table;
    EXPECT_TRUE(table.empty());
}

TEST(test_table , is_empty_2_insert_and_erase) {
    HashTable table;
    std::string key = gen_str(rand() % 20);
    const Value t(key, rand() % 20);
    table.insert(key, t);
    table.erase(key);
    EXPECT_TRUE(table.empty());
}

TEST(test_table , is_not_empty_1) {
    HashTable table;
    std::string key = gen_str(rand() % 20);
    const Value t(gen_str(rand() % 20), rand() % 20);
    table.insert(key, t);
    EXPECT_FALSE(table.empty());
}

TEST(test_table , is_not_empty_if_many_inserted) {
    HashTable table;
    std::string key = gen_str(rand() % 20);
    for( int i = 0 ; i < 1000 ; i++){
        const Value t(key, rand() % 20);
        table.insert(key, t);
    }
    EXPECT_FALSE(table.empty());
}


//contains
TEST(test_table , contains) {
    HashTable table;
    std::string key = gen_str(rand() % 20);
    const Value t(gen_str(rand() % 20), 10);
    table.insert(key, t);
    EXPECT_TRUE(table.contains(key));
}

TEST(test_table , there_is_not_such_key) {
    HashTable table;
    const Value t("Mark", 10);
    table.insert("hello", t);
    EXPECT_FALSE(table.contains("sodajioadsba") );
}

// operator ==
TEST(test_table , empty_tables_are_equal) {
    HashTable table;
    HashTable table_1;
    EXPECT_TRUE(table == table_1 );
}
TEST(test_table , are_equal) {
    HashTable table;
    HashTable table_1;    
    const Value a("Mark", 10);
    const Value b("Maxim", 15);
    
    table.insert("hello", a);
    table.insert("hello", b);

    table_1.insert("hello", a);
    table_1.insert("hello", b);
    EXPECT_TRUE(table == table_1 );
}

TEST(test_table , are_not_equal_if_different_size) {
    HashTable table;
    HashTable table_1;    
    const Value a("Mark", 10);
    table_1.insert(gen_str(rand() % 20), a);
    EXPECT_FALSE(table == table_1);
}

TEST(test_table , are_not_equal_same_value_different_keys) {
    HashTable table;
    HashTable table_1;    
    const Value a("Mark", 10);
    table.insert("wqer", a);
    table_1.insert("hello", a);
    EXPECT_FALSE(table == table_1);
}

TEST(test_table , are_not_equal_2_different_key_but_equal_hash) {
    HashTable table(1);
    HashTable table_1(1);
    const Value a("Mark", 10);
    table.insert("j", a);
    table_1.insert("h", a);
    EXPECT_FALSE(table == table_1);
}

TEST(test_table , are_not_equal_3) {
    HashTable table;
    HashTable table_1;
    const Value a("Mark", 10);
    table.insert("hello", a);
    table_1.insert("dsa", a);
    table_1.insert("hello", a);
    EXPECT_FALSE(table == table_1);
}

//erase
TEST(test_table , erase_to_empty_table) {
    HashTable table;
    EXPECT_FALSE(table.erase(gen_str(rand() % 20)));
    EXPECT_EQ(table.size() , 0);
}
TEST(test_table , erase_exists_cell) {
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Maxim", 15);
    table.insert("hello", a);
    table.insert("sdf", b);
    table.erase("hello");
    EXPECT_EQ(table.size() , 1);
}

TEST(test_table , erase_not_exists_cell) {
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Maxim", 15);
    table.insert("hello", a);
    table.insert("sdf", b);
    table.erase("fwq");
    EXPECT_EQ(table.size() , 2);
}

TEST(test_table , erase_couple_equal_value) {
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Mark", 10);
    table.insert("hello", a);
    table.insert("hello", b);
    table.erase("hello");
    EXPECT_EQ(table.size() , 0);
}

// copy ctor

TEST(test_table , assign_and_compare_empty_tables) {
    HashTable table;
    HashTable table_1 = table;
    EXPECT_TRUE(table_1 == table );
}   

TEST(test_table , assign_and_compare_not_empty_tables) {
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Mark", 10);
    table.insert("dsaf", a);
    table.insert("dsadsf", b); 
    EXPECT_EQ(table.size() , 2);
    HashTable table_1 = table;
    EXPECT_TRUE(table_1 == table);
}   

//operator =
TEST(test_table , assign_and_compare_empty_tables_1) {
    HashTable table;
    HashTable table_1;
    table_1 = table;
    EXPECT_TRUE(table_1 == table );
}   

TEST(test_table , assign_and_compare_not_empty_tables_1) {
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Mark", 10);
    table.insert("dsaf", a);
    table.insert("dsadsf", b); 
    HashTable table_1;
    table_1.insert("dsaf", a);
    table_1.insert("dsadsf", b); 
    table_1 = table;
    EXPECT_TRUE(table_1 == table);
}  

//operator !=
TEST(test_table , assign_and_compare_empty_tables_7) {
    HashTable table;
    HashTable table_1 = table;
    EXPECT_FALSE(table_1 != table );
}   

TEST(test_table , assign_and_compare_no_find){
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Mark", 10);
    table.insert("dsaf", a);
    table.insert("dsadsf", b); 
    HashTable table_1 = table;
    EXPECT_FALSE(table_1 != table);
}   

// at
TEST(test_table , at_not_exist_value_cell) {
    HashTable table;
    ASSERT_THROW(table.at(gen_str(rand() % 20)) , std::runtime_error);
}   

TEST(test_table , at_not_exist_value_2) {
    HashTable table;
    const Value a(gen_str(rand() % 20), 21);
    table.insert("asdfsa", a);
    ASSERT_THROW(table.at("hjkasdjhsa"), std::runtime_error);
}   

TEST(test_table , at_exist_value_3) { 
    HashTable table;
    std::string name = gen_str(rand() % 20);
    std::string key = gen_str(rand() % 20);
    const Value a(name, 21);
    table.insert(key, a);
    Value c = table.at(key);
    EXPECT_TRUE(compare(c , a));
}   

//operator=
TEST(test_table , assign_empty_table_to_empty_table) {
    HashTable table;
    HashTable table_1;
    table_1 = table;
    EXPECT_TRUE( table == table_1);
}   

TEST(test_table , assign_empty_table_to_not_empty_table ) {
    HashTable table;
    HashTable table_1;
    const Value c(gen_str(rand() % 20), 10);
    table.insert(gen_str(rand() % 20), c); 
    table_1 = table;
    EXPECT_TRUE( table == table_1);
}   

TEST(test_table , assign_not_empty_table_to_empty_table ) {
    HashTable table;
    HashTable table_1;
    const Value c(gen_str(rand() % 20), 10);
    table.insert(gen_str(rand() % 20), c); 
    table = table_1;
    EXPECT_TRUE( table == table_1);
}   

TEST(test_table , assign_not_empty_table_to_not_empty_table) {
    HashTable table;
    const Value a(gen_str(rand() % 20), 10);
    const Value b(gen_str(rand() % 20), 10);
    table.insert(gen_str(rand() % 20), a);
    table.insert(gen_str(rand() % 20), b); 
    HashTable table_1;
    const Value c(gen_str(rand() % 20), 10);
    table.insert(gen_str(rand() % 20), c); 
    table_1 = table;
    EXPECT_TRUE( table == table_1);
}   


//swap
TEST(test_table , swap_not_empty_tables_equal_capacity_and_size) {
    HashTable table;
    HashTable table_1;
    const Value a(gen_str(rand() % 20), 21);
    const Value b(gen_str(rand() % 20), 121);
    table.insert(gen_str(rand() % 20), a);
    table_1.insert(gen_str(rand() % 20), b);  
    HashTable copy_table = table;
    HashTable copy_table_1 = table_1;
    table.swap(table_1);
    EXPECT_TRUE( table == copy_table_1);
    EXPECT_TRUE( table_1 == copy_table);
}   

TEST(test_table , swap_not_empty_tables_with_itself_equal_capacity_and_size ) {
    HashTable table;
    const Value a(gen_str(rand() % 20), 21);
    const Value b(gen_str(rand() % 20), 121);
    table.insert(gen_str(rand() % 20), a);
    table.insert(gen_str(rand() % 20), b);  
    HashTable table_1 = table;
    table.swap(table);
    EXPECT_TRUE(table == table_1);
}   

TEST(test_table , swap_empty_tables ) {
    HashTable table;
    HashTable table_1;
    HashTable copy_table = table;
    HashTable copy_table_1 = table_1;
    table.swap(table_1);
    EXPECT_TRUE( table == copy_table_1);
    EXPECT_TRUE( table_1 == copy_table );
}   

TEST(test_table , swap_tables_with_different_size_and_equal_capacity ) {
    HashTable table;
    HashTable table_1;
    const Value a(gen_str(rand() % 20), 21);
    const Value b(gen_str(rand() % 20), 121);
    const Value d(gen_str(rand() % 20), 23);
    table.insert(gen_str(rand() % 20), a);
    table.insert(gen_str(rand() % 20), b);  
    table_1.insert(gen_str(rand() % 20), d);

    HashTable copy_table = table;
    HashTable copy_table_1 = table_1;
    table.swap(table_1);

    EXPECT_TRUE( table == copy_table_1);

    EXPECT_TRUE( table_1 == copy_table );
}   

TEST(test_table , swap_tables_with_different_size_and_different_capacity ) {
    HashTable table;
    HashTable table_1;
    const Value a(gen_str(rand() % 20), 21);
    const Value b(gen_str(rand() % 20), 121);
    const Value e(gen_str(rand() % 20), 11);
    const Value d(gen_str(rand() % 20), 23);
    table.insert(gen_str(rand() % 20), a);
    table.insert(gen_str(rand() % 20), b);  
    table.insert(gen_str(rand() % 20), e);  
    table_1.insert(gen_str(rand() % 20), d);

    HashTable copy_table = table;
    HashTable copy_table_1 = table_1;
    table.swap(table_1);

    EXPECT_TRUE( table == copy_table_1);

    EXPECT_TRUE( table_1 == copy_table);
}   

TEST(test_table , swap_empty_and_not_empty_tables ) {
    HashTable table;
    HashTable table_1;
    const Value a(gen_str(rand() % 20), 21);
    const Value b(gen_str(rand() % 20), 121);
    const Value e(gen_str(rand() % 20), 11);
    
    table.insert(gen_str(rand() % 20), a);
    table.insert(gen_str(rand() % 20), b);  

    HashTable copy_table = table;
    HashTable copy_table_1 = table_1;
    table.swap(table_1);

    EXPECT_TRUE( table == copy_table_1);

    EXPECT_TRUE( table_1 == copy_table);
}   

//clear
TEST(test_table , clear_empty_table ) {
    HashTable table;
    table.clear();
    EXPECT_EQ(table.size() , 0);
} 

TEST(test_table , clear_not_empty_table_1 ) {
    HashTable table;
    for(int i = 0 ; i < rand() % 100 ; i++){
        const Value a(gen_str(rand() % 20), 10);
        table.insert(gen_str(rand() % 20), a);
    }
    table.clear();
    EXPECT_EQ(table.size() , 0);
}   

TEST(test_table , clear_not_empty_table_2_and_insert) {
    HashTable table;
    const Value a(gen_str(rand() % 20), 21);
    const Value b(gen_str(rand() % 20), 121);
    const Value d(gen_str(rand() % 20), 23);
    table.insert(gen_str(rand() % 20), a);
    table.insert(gen_str(rand() % 20), b);  
    table.insert(gen_str(rand() % 20), d);
    table.clear();
    table.insert(gen_str(rand() % 20), d);
    EXPECT_EQ(table.size() , 1);
}   


//operator[]

TEST(test_table , accessing_an_empty_cell) {
    HashTable table;
    std::string key = gen_str(rand() % 20);
    Value v("" , 0);
    EXPECT_TRUE(compare(table[key] , v));
}   

TEST(test_table , accessing_an_not_empty_cell) {
    HashTable table;
    const Value a(gen_str(rand() % 20), 10);
    std::string key = gen_str(rand() % 20);
    table.insert(key, a);
    EXPECT_TRUE(compare(table[key] , a));
}   
