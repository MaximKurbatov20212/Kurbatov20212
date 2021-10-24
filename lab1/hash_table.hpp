#ifndef HASH_TABLE
#define HASH_TABLE

#define MIN_SIZE 2 // простое
#define PRIME_1 7

typedef std::string Key;

typedef struct Value {
    Value() = default;
    Value(std::string n, unsigned a = 0) : name(n), age(a) {}
    std::string name;
    unsigned age;
}Value;

struct Cells {
    Cells() = default;
    Cells(Key k, const Value* v) : key(k), value(v) {}
    const Value* value;
    Key key;
};

class HashTable {
private:
    const Cells** cells;
    int size_;
    int capacity_;

    void free_cells();

    void copy_cells(const Cells** to, const Cells** from, int capacity);

    void rebuld_table(const Cells** array);//+

    bool is_occupied(int pos);//+

    bool resize();//+

    unsigned int calc_hash(std::string expression) const;//+

    void init_cells(const Cells** cells);//+

public:
    HashTable();//+
    // Allocate memory to table

    ~HashTable();//+
    // Delete table

    HashTable& operator=(const HashTable& b);//+
    // Assign b to this, if b is not equal this and returns this

    HashTable(const HashTable& b);//+

    void print_table();///+
    // Prints all cells of table, prints "There is noting in ____" if cell is empty

    void swap(HashTable& b);//+
    // Change corresponding cells in two tabels.

    void clear();//+
    // Delete all cells and init their again.

    bool erase(const Key& k);//+
    // Delete first cell in table with equal key
    // Returns true, if there is cell with current key
    // Returns false, if there is not cell with current key

    bool insert(const Key& k, const Value& v);//+
    // Create and insert v to table in corresponding cell, depending to k
    // If cell is occupied then increase index to one and try again 
    // If table is full then increase capacity of table and insert v
    // Assert if can not allocates memory, else returns true

    bool contains(const Key& k) const; //+
    // Return true, if table contains cell with key k
    // Return false,  if there is not cell with key k


    Value& operator[](const Key& k);//+
    // Returns link for exist value in table, if there is cell with key k
    // Assert if there is not cell with such key


    Value& at(const Key& k);//+
    // Returns link for exist value in table, if there is cell with key k
    // Create new value with key k, if there is not cell with key k

    const Value& at(const Key& k) const;//+
    // Returns constant link for exist value in table, if there is cell with key k
    // Create new value with key k, if there is not cell with key k

    size_t size() const;//+
    // Returns count of not empty cells in table

    size_t capacity() const;//+
    // Return count of all cells in table

    bool empty() const;//+
    // Returns true, if table has not initialazed cells.
    // Return false, if there is one or more initialazed cells

    friend bool operator==(const HashTable& a, const HashTable& b);//+
    // Compare all cells of tables.
    // Returns true, if all of corresponding cells are equal
    // Returns false, if exist different cells with equal index

    friend bool operator!=(const HashTable& a, const HashTable& b);//+
    // Compare all cells of tables.
    // Returns false, if all of corresponding cells are equal
    // Returns true, if exist different cells with equal index
};
#endif