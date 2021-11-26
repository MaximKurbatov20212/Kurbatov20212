#ifndef HASH_TABLE
#define HASH_TABLE
typedef std::string Key;

struct Value {
    Value() = default;
    explicit Value(std::string n, unsigned a = 0) : name(n), age(a) {}
    std::string name;
    unsigned age;
};

class HashTable {
public:
    explicit HashTable(int capacity = MIN_CAPACITY);

    ~HashTable();

    // Assign b to this, if b is not equal to this and returns this
    HashTable& operator=(const HashTable& b);

    HashTable(const HashTable& b);

    // Prints all cells of table, prints "cells[i] = nullptr" if cell is empty
    friend std::ostream& operator<< (std::ostream &out, const HashTable& a);

    // Changes cells in two tabels with equal index. 
    void swap(HashTable& b);

    // Deletes all cells but don't delete table.
    void clear();

    // Deletes cell in the table with such key and shifts all top cells 1 position down(if the cell below the current is not nullptr)
    // Returns true, if there is cell with current key
    // Returns false, if there is no cell with current key
    bool erase(const Key& k);

    // Creates and inserts v to table.
    // If there is cell this such key then don't insert and return false.
    bool insert(const Key& k, const Value& v);

    // Returns true, if table contains cell with such key
    // Returns false, if there is no cell with such key
    bool contains(const Key& k) const;

    // Returns link to exist value in the table, if there is cell with such key
    // Creates new value with key k, name = "", age = 0, if there is no cell with such key
    Value& operator[](const Key& k);

    // Returns link to exist value in the table, if there is cell with such key
    // Exeption(std::runtime_error) if there is no cell with such key
    Value& at(const Key& k);

    // Returns constant link to exist value in the table, if there is cell with such key
    // Exeption(std::runtime_error) if there is no cell with such key
    const Value& at(const Key& k) const;

    // Returns count of not empty cells in the table
    size_t size() const;

    // Returns count of all cells in the table
    size_t capacity() const;

    // Returns true, if table has not initialazed cells.
    // Returns false, if there is one or more initialazed cells
    bool empty() const;

    // Returns true, if the tables have the same cells (not necessarily in the same order)
    // Else returns false
    friend bool operator==(const HashTable& a, const HashTable& b);

    // Returns false, if the tables have the same cells (not necessarily in the same order)
    // Else returns true
    friend bool operator!=(const HashTable& a, const HashTable& b);

    // Compares all cells in the tables.
    // Returns false, if cells with equal index are equal
    // Returns true, if exist different cells with equal index
    friend bool compare_cells(const HashTable& a, const HashTable& b);

    int my_find(const Key& k){ return find(k); }; // for testing
private:
    int capacity_;
    int size_;

    struct Cell {
        Key key;
        const Value value;
        Cell(Key k, const Value v) : key(k), value(v) {};
    };

    const Cell** cells;

    const static size_t PRIME_1 = 7;
    const static size_t MIN_CAPACITY = 4;

    void free_cells();

    static void copy_cells(const Cell** to, const Cell** from, int capacity);

    bool resize();

    unsigned int calc_hash(const std::string& expression) const;

    int find(const Key& k) const;

    bool insert(const Key& k, const Value& v, int capacity, const Cell** array);
};
#endif