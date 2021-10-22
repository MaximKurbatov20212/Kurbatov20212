#include <gtest/gtest.h>
#include "hash_table.hpp"
#include <ctime>
#include <unistd.h>
#include <limits.h>
#define MYTESTS mytests

// random string
std::string gen_rand(const int len) {
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

//insert
TEST(MYTESTS , initial_size_is_zero) {
    HashTable table;
    EXPECT_EQ(table.size() , 0);
}

TEST(MYTESTS , insert_one_value) {
    HashTable table;
    const Value t(gen_rand(rand() % 20), 21);
    table.insert(gen_rand(rand() % 20), t);
    EXPECT_EQ(table.size() , 1);
}

TEST(MYTESTS , insert_two_equal_value) {
    HashTable table;
    std::string str = gen_rand(rand() % 20);
    std::string key = gen_rand(rand() % 20);
    const Value a(str, 20);
    const Value b(str, 20);
    table.insert(key, a);
    table.insert(key, b);
    EXPECT_EQ(table.size() , 2);
}

TEST(MYTESTS , insert_many_values) {
    HashTable table;
    size_t range = rand() % 100;
    for(int i = 0 ; i < range ; i++){
        const Value a( gen_rand(rand() % 20) , rand() % 100);
        table.insert( gen_rand(rand() % 20) , a);
    }
    EXPECT_EQ(table.size() , range);
}

TEST(MYTESTS , couple_of_equial_value) {
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Maxim", 15);
    table.insert("hello", a);
    table.insert("hello", b);
    EXPECT_EQ(table.size() , 2);
}

// TEST(MYTESTS , memory) {
//     HashTable table;
//     for(long long i = 0 ; i < LLONG_MAX ; i++){
//         const Value a( gen_rand(rand() % 20) , rand() % 100);
//         ASSERT_DEATH(table.insert( gen_rand(rand() % 20) , a), "Assertion failed.*");
//     }
// }

//empty
TEST(MYTESTS , is_empty_1) {
    HashTable table;
    EXPECT_EQ(table.empty() , 1);
}

TEST(MYTESTS , is_empty_2_insert_and_erase) {
    HashTable table;
    std::string key = gen_rand(rand() % 20);
    const Value t(key, rand() % 20);
    table.insert(key, t);
    table.erase(key);
    EXPECT_EQ(table.empty() , 1);
}

TEST(MYTESTS , is_not_empty_1) {
    HashTable table;
    std::string key = gen_rand(rand() % 20);
    const Value t(gen_rand(rand() % 20), rand() % 20);
    table.insert(key, t);
    EXPECT_EQ(table.empty() , 0);
}

TEST(MYTESTS , is_not_empty_2) {
    HashTable table;
    std::string key = gen_rand(rand() % 20);
    for( int i = 0 ; i < 1000 ; i++){
        const Value t(key, rand() % 20);
        table.insert(key, t);
    }
    EXPECT_EQ(table.empty() , 0);
}


//contains
TEST(MYTESTS , contains) {
    HashTable table;
    std::string key = gen_rand(rand() % 20);
    const Value t(gen_rand(rand() % 20), 10);
    table.insert(key, t);
    EXPECT_EQ(table.contains(key) , 1);
}

TEST(MYTESTS , there_is_not_such_key) {
    HashTable table;
    const Value t("Mark", 10);
    table.insert("hello", t);
    EXPECT_EQ(table.contains("qwe") , 0);
}

// operator ==
TEST(MYTESTS , init_table_is_equal) {
    HashTable table;
    HashTable table_1;
    EXPECT_EQ(table == table_1 , 1);
}
TEST(MYTESTS , is_equal) {
    HashTable table;
    HashTable table_1;    
    const Value a("Mark", 10);
    const Value b("Maxim", 15);
    
    table.insert("hello", a);
    table.insert("hello", b);

    table_1.insert("hello", a);
    table_1.insert("hello", b);
    EXPECT_EQ(table == table_1 , 1);
}

TEST(MYTESTS , is_not_equal) {
    HashTable table;
    HashTable table_1;    
    const Value a("Mark", 10);
    table_1.insert(gen_rand(rand() % 20), a);
    EXPECT_EQ(table == table_1 , 0);
}

TEST(MYTESTS , is_not_equal_1) {
    HashTable table;
    HashTable table_1;    
    const Value a("Mark", 10);
    table.insert("wqer", a);
    table_1.insert("hello", a);
    EXPECT_EQ(table == table_1 , 0);
}

TEST(MYTESTS , is_not_equal_2_different_key_but_equal_hash) {
    HashTable table;
    HashTable table_1;    
    const Value a("Mark", 10);
    table.insert("j", a);
    table_1.insert("h", a);
    EXPECT_EQ(table == table_1 , 0);
}

TEST(MYTESTS , is_not_equal_3) {
    HashTable table;
    HashTable table_1;
    const Value a("Mark", 10);
    table.insert("hello", a);
    table_1.insert("dsa", a);
    table_1.insert("hello", a);
    EXPECT_EQ(table == table_1 , 0);
}

//erase
TEST(MYTESTS , erase_to_empty_table) {
    HashTable table;
    table.erase(gen_rand(rand() % 20));
    EXPECT_EQ(table.size() , 0);
}
TEST(MYTESTS , erase_exists_cell) {
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Maxim", 15);
    table.insert("hello", a);
    table.insert("sdf", b);
    table.erase("hello");
    EXPECT_EQ(table.size() , 1);
}

TEST(MYTESTS , erase_not_exists_cell) {
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Maxim", 15);
    table.insert("hello", a);
    table.insert("sdf", b);
    table.erase("fwq");
    EXPECT_EQ(table.size() , 2);
}

TEST(MYTESTS , erase_couple_equal_value) {
    HashTable table;
    const Value a("Mark", 10);
    const Value b("Mark", 10);
    table.insert("hello", a);
    table.insert("hello", b);
    table.erase("hello");
    EXPECT_EQ(table.size() , 1);
}



int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}