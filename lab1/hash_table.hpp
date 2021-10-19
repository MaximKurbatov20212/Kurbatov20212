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

    void rebuld_table(const Cells** array);//+

    bool is_occupied(int pos);//+

    bool resize();//+

    int calc_hash(std::string expression) const;//+

    void init_cells(const Cells** cells);//+

public:
    HashTable();//+
    ~HashTable();//+

    HashTable& operator=(const HashTable& b);//+

    HashTable(const HashTable& b);//+

    void print_table();///+

    void swap(HashTable& b);//+

    void clear();//+

    bool erase(const Key& k);//+

    bool insert(const Key& k, const Value& v);//+

    bool contains(const Key& k) const; //+

    Value& operator[](const Key& k);//+

    Value& at(const Key& k);//+

    const Value& at(const Key& k) const;//+

    size_t size() const;//+

    size_t capacity() const;//+

    bool empty() const;//+

    friend bool operator==(const HashTable& a, const HashTable& b);//+
    friend bool operator!=(const HashTable& a, const HashTable& b);//+
};
