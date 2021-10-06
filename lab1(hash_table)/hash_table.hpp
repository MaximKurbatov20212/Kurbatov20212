#define MIN_SIZE 13 // простое
#define PRIME_1 7
#define PRIME_2 11
typedef std::string Key;

typedef struct Value {
    Value() = default;
    Value(std::string n, unsigned a = 0) : name(n), age(a) {}
    std::string name;
    unsigned age;
}Value;


class HashTable {
private:
    Value* array;
    int size_;
    int capacity_;
public:
    HashTable();
    ~HashTable();
    bool is_occupied(int pos);
    HashTable& operator=(const HashTable& b);

    HashTable(const HashTable& b);

    void print_table();

    bool resize();

    int calc_main_hash(std::string expression);

    int calc_extra_hash(std::string expression);

    void swap(HashTable& b);

    void clear();

    bool erase(const Key& k);

    bool insert(const Key& k, const Value& v);

    bool contains(const Key& k) const;
  
    Value& operator[](const Key& k);

    Value& at(const Key& k);

    const Value& at(const Key& k) const;
  
    size_t size() const ;

    size_t capacity() const ;

    bool empty() const;


    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);
};
