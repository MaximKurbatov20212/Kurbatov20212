#ifndef HASH_TABLE
#define HASH_TABLE

typedef std::string Key;

typedef struct Value {
    Value() = default;
    Value(std::string n, unsigned a = 0) : name(n), age(a) {}
    std::string name;
    unsigned age;
}Value;

 
class HashTable {
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
    const static size_t MIN_SIZE  = 2;

    void free_cells();

    void copy_cells(const Cells** to, const Cells** from, int capacity);

    void rebuld_table(const Cells** array); 

    bool is_occupied(int pos); 

    bool resize(); 

    unsigned int calc_hash(std::string expression) const; 

    const Cells* find(const Key & k) const; 

public:

    HashTable();
    HashTable(int c); 

    ~HashTable(); 

    // Assign b to this, if b is no equal this and returns this
    HashTable& operator=(const HashTable& b); 
    
    HashTable(const HashTable& b); 

    // Prints all cells of table, prints "There is noting in ____" if cell is empty
    void print_table();

    // Change cells in two tabels with equal index. 
    void swap(HashTable& b); 
    
    // Delete all cells and init their again. 
    void clear(); 


    // Delete first cell in the table with equal key
    // Returns true, if there is cell with current key
    // Returns false, if there is no cell with current key

    bool erase(const Key& k); 


    // Create and insert v to table in corresponding cell, depending to k
    // If cell is occupied then increase index to one and try again 
    // If table is full then increase capacity of table and insert v
    // Assert if can no allocates memory, else returns true
    bool insert(const Key& k, const Value& v); 


    // Return true, if table contains cell with key k
    // Return false, if there is no cell with key k
    bool contains(const Key& k) const;  


    // Returns link to exist value in the table, if there is cell with key k
    // Create new value with key k, name = "", age = 0, if there is no cell with key k
    Value& operator[](const Key& k); 


    // Returns link to exist value in the table, if there is cell with key k
    // Assert if there is no cell with such key
    Value& at(const Key& k); 

    // Returns constant link to exist value in the table, if there is cell with key k
    // Assert if there is no cell with such key
    const Value& at(const Key& k) const; 


    // Returns count of no empty cells in the table
    size_t size() const; 

    // Return count of all cells in the table
    size_t capacity() const; 


    // Returns true, if table has no initialazed cells.
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


   
};
#endif