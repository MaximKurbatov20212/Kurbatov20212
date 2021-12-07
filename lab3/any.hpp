

template<typename T> 
class Any {
public:
    Any();
    Any(const Any &);
    Any(Any &&);
    Any(const T &);
    Any(T &&);
    Any & operator=(const Any &);
    Any & operator=(Any &&);
    Any & operator=(const T &);
    Any & operator=(T &&);
    ~Any();

    // modifiers
    Any & swap(Any &);

    // queries
    bool empty() const;
    const std::type_info & type() const;
private:
    T value_;
};
