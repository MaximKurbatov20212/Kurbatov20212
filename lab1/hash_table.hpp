#ifndef HASH_TABLE
#define HASH_TABLE
typedef std::string Key;

typedef struct Value {
    Value() = default;
    Value(std::string n, unsigned a = 0) : name(n), age(a) {}
    std::string name;
    unsigned age;

    void operator=(const Value& v) {
        age = v.age;
        name = v.name;
    }
}Value;


class HashTable {
public:

    HashTable();
    HashTable(int capacity);

    ~HashTable();

    // Assign b to this, if b is not equal this and returns this
    HashTable& operator=(const HashTable& b);

    HashTable(const HashTable& b);

    // Prints all cells of table, prints "cells[i] = nullptr" if cell is empty
    void print_table();

    // Change cells in two tabels with equal index. 
    void swap(HashTable& b);

    // Delete all cells but don't delete table.
    void clear();

    // Delete cell in the table with such key
    // Returns true, if there is cell with current key
    // Returns false, if there is no cell with current key
    bool erase(const Key& k);


    // Create and insert v to table.
    // If cell is occupied then increase index to one and try again
    // If there is cell this such key then don't insert and return false.
    // If table is more then 75% full then increase capacity of table and insert v
    bool insert(const Key& k, const Value& v);


    // Return true, if table contains cell with such key
    // Return false, if there is no cell with such key
    bool contains(const Key& k) const;


    // Returns link to exist value in the table, if there is cell with such key
    // Create new value with key k, name = "", age = 0, if there is no cell with such key
    Value& operator[](const Key& k);


    // Returns link to exist value in the table, if there is cell with such key
    // Exeption(std::runtime_error) if there is no cell with such key
    Value& at(const Key& k);

    // Returns constant link to exist value in the table, if there is cell with such key
    // Exeption(std::runtime_error) if there is no cell with such key
    const Value& at(const Key& k) const;

    // Returns count of not empty cells in the table
    size_t size() const;

    // Return count of all cells in the table
    size_t capacity() const;


    // Returns true, if table has not initialazed cells.
    // Return false, if there is one or more initialazed cells
    bool empty() const;

    //Compare all cells of tables.
    //Returns true, if all of corresponding cells are equal
    //Returns false, if exist different cells with equal index
    friend bool operator==(const HashTable& a, const HashTable& b);


    // Compare all cells of tables.
    // Returns false, if all of corresponding cells are equal
    // Returns true, if exist different cells with equal index
    friend bool operator!=(const HashTable& a, const HashTable& b);

private:
    int capacity_;
    int size_;

    struct Cells {
        Key key;
        const Value value;
        Cells() = default;
        Cells(Key k, const Value v) : key(k), value(v) {}
    };

    const Cells** cells;

    const static size_t PRIME_1 = 7;
    const static size_t MIN_SIZE = 11;

    void free_cells();

    void copy_cells(const Cells** to, const Cells** from, int capacity);

    void rebuld_table(const Cells** array);

    bool is_occupied(int pos);

    bool resize();

    unsigned int calc_hash(std::string expression) const;

    void init_cells();

    int find(const Key& k) const;

    bool insert(const Key& k, const Value& v, int capacity, const Cells** array);


};
#endif