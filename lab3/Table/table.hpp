#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <cassert>
#include <limits>
#include <algorithm>
#include <functional>

template<std::default_initializable Value, std::default_initializable Key>
struct MyPair {
    Value value = Value{};
    Key key = Key{};
    MyPair(Value v, Key k): value(v), key(k){}
    MyPair() : value(), key() {}
    bool operator==(const MyPair& other) const {
        return (this->key == other.key) && (this->value == other.value);
    }
};

template<std::default_initializable Value, std::default_initializable Key>
class Table;


template <std::default_initializable MyPair>
struct Node {
    MyPair node = MyPair{};
    Node* next = nullptr;
};

/*!
 * @brief The iterator class for the table
 * @tparam Key the key of the element
 * @tparam Value the value of the element
 * @tparam is_const iterator is const_iterator if true,
 *         the usual iterator otherwise
 */
template<std::default_initializable Value, std::default_initializable Key, bool is_const>
class TableIterator {
public:
    /*!
    * @brief A type indicating the distance between two iterators
    */
    typedef ptrdiff_t difference_type;

    /*!
    * @brief The type addressed by the iterator
    */
    typedef MyPair<Value, Key> value_type;

    /*!
    * @brief The type of pointer to a stored value
    */
    typedef std::conditional_t<is_const, const MyPair<Value, Key>, MyPair<Value, Key>>* pointer;

    /*!
    * @brief The type of reference to the stored value
    */
    typedef std::conditional_t<is_const, const MyPair<Value, Key>, MyPair<Value, Key>>& reference;
    
    /*!
    * @brief Category iterator
    */
    typedef std::forward_iterator_tag iterator_category;

    /*!
    * @brief Empty constructor
    */
    TableIterator() noexcept;

    /*!
    * @brief The copying constructor
    * @tparam other_const The constancy of the copied iterator
    * @note allows copying an iterator of a different constancy
    * @note implements std::move_constructible and std::copy_constructible
    */
    template<bool other_const> 
    TableIterator(const TableIterator<Value, Key, other_const>& o) noexcept
        requires (is_const >= other_const);

    /*!
    * @brief Copying movement
    * @returns Reference to the passed iterator
    * @tparam other_const The constancy of the iterator being copied
    * @note Allows copying an iterator of a different constancy
    * @note Implements std::assignable_from, std::copyable and std::swappable
    */
    template<bool other_const> 
    TableIterator& operator = (const TableIterator<Value, Key, other_const>& o) noexcept
        requires (is_const >= other_const);

    /*!
    * @brief Dereference
    * @returns A link to the addressable list item
    */
    reference operator * () const noexcept;

    /*!
    * @brief Accessing element fields
    * @returns A pointer to the addressable list item
    */
    pointer operator -> () const noexcept;

    /*!
    * @brief Comparison of iterators
    * @tparam other_const The constancy of the iterator being copied
    * @returns true if iterators refer to the same element,
                  * otherwise false
    * @note Implements equality_comparable from regular
    * @note Operator != we get it automatically
    */
    template<bool other_const> bool operator == (const TableIterator<Value, Key, other_const>& o) const noexcept;
    
    /*!
    * @brief Moves the iterator to the next item in the table
    * @returns Link to the passed iterator
    */
    TableIterator& operator ++ () noexcept;

    /*!
    * @brief Moves the iterator to the next item in the table
    * @returns The state of the iterator before modification
    */
    TableIterator operator ++ (int) noexcept;


private:
    // The type of pointer to the table node
    typedef std::conditional_t<is_const, const Node<MyPair<Value, Key>>, Node<MyPair<Value, Key>>>* node_ptr_t;

    // The node that the iterator points to
    node_ptr_t node;

    // The constructor in the private area
    TableIterator(node_ptr_t node);
    friend Table<Value, Key>;
    friend TableIterator<Value, Key, !is_const>;
};

/*!
* @brief The table being viewed
* @tparam Key the key of the element
* @tparam Value the value of the element
*/
template<std::default_initializable Value, std::default_initializable Key>
class Table {
public:
    /*!
    * @brief Type of value
    */
    typedef Value value_type;

    /*!
    * @brief Type of key
    */
    typedef Key key_type;

    /*!
    * @brief Type of stored values
    */
    typedef MyPair<Value, Key> node_type;

    /*!
    * @brief Reference to the type of stored values
    */
    typedef MyPair<Value, Key>& reference;

    /*!
    * @brief Constant reference to the type of stored values
    */
    typedef const MyPair<Value, Key>& const_reference;

    /*!
    * @brief Iterator type
    */
    typedef TableIterator<Value, Key, false> iterator;

    /*!
    * @brief Type of constant iterator
    */
    typedef TableIterator<Value, Key, true> const_iterator;

    /*!
    * @brief Type indicating the distance between two iterators
    */
    typedef ptrdiff_t difference_type;

    /*!
    * @brief The type used to represent the size of the container
    */
    typedef size_t size_type;

    /*!
    * @brief Empty constructor, creates an empty table
    */
    Table() noexcept(std::is_nothrow_default_constructible_v<MyPair<Value, Key>>);

    /*!
    * @brief Copying Constructor
    * @param o The table being copied
    */
    Table(const Table& o)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Moving constructor
    * @param o A movable table
    */
    Table(Table&& o)
        noexcept(std::is_nothrow_default_constructible_v<MyPair<Value, Key>>);

    /*!
    * @brief Constructor that fills the table with n copies of mp
    * @param n Number of elements
    * @param mp is the value of the element that the table will be filled with
    */
    Table(size_type n, const MyPair<Value, Key>& mp)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Constructor that fills the table with elements from the range [i, j)
    * @param i The beginning of the range to copy
    * @param j End of range to copy
    */
    template<std::input_iterator It>
    Table(It i, It j)
        requires std::constructible_from<MyPair<Value, Key>, std::iter_reference_t<It>>;

    /*!
    * @brief Constructor that fills the table with elements from the initialization list
    * @param il inisializer_list from which the values will be copied
    */
    Table(std::initializer_list<MyPair<Value, Key>> il)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Copying assignment operator
    * @param o The table being copied
    */
    Table& operator = (const Table& o)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Moving assignment operator
    * @param o A movable table
    */
    Table& operator = (Table&& o) noexcept;

    /*!
    * @brief Comparison of iterators
    * @param o the table being compared
    */
    bool operator == (const Table& o) const;

    /*!
    * @brief Destructor
    */
    ~Table();

    /*!
    * @brief Getting the iterator to the top of the table
    * @returns Iterator addressing the beginning of the table
    */
    iterator begin() noexcept;

    /*!
    * @brief Getting the iterator to the end of the table
    * @returns Iterator addressing the end of the table
    */
    iterator end() noexcept;

    /*!
    * @brief Getting a constant iterator to the top of the table
    * @returns Iterator addressing the beginning of the table
    */
    const_iterator begin() const noexcept;

    /*!
    * @brief Getting a constant iterator to the end of the table
    * @returns Iterator addressing the end of the table
    */
    const_iterator end() const noexcept;

    /*!
    * @brief Getting a constant iterator to the top of the table
    * @returns Iterator addressing the beginning of the table
    */
    const_iterator cbegin() const noexcept;

    /*!
    * @brief Getting a constant iterator to the end of the table
    * @returns Iterator addressing the end of the table
    */
    const_iterator cend() const noexcept;

    /*!
    * @brief Exchanges the states of two tables with each other
    * @param o Table for sharing status
    */
    void swap(Table& o) noexcept;

    /*!
    * @brief Returns the size of the container
    * @returns Container size
    */
    size_type size() const noexcept;

    /*!
    * @brief Returns the maximum possible container size
    * @returns The maximum possible container size
    */
    size_type max_size() const noexcept;

    /*!
    * @brief Checking the table for emptiness
    * @returns true if the table is empty, otherwise false
    */
    bool empty() const noexcept;

    /*!
    * @brief Assignment operator that fills the list with elements
            * from the initialization list
    * @param il initializer_list from which values will be copied
    */
    Table& operator = (std::initializer_list<MyPair<Value, Key>> il)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Inserting an element constructed in the table
            * from the transmitted values
    * @param p Iterator, after which a new element will be inserted
    * @param args Values to pass to the element constructor
    * @returns Iterator on the inserted element
    */
    template<typename ... Args>
    iterator emplace(iterator p, Args && ... args)
        requires std::constructible_from<MyPair<Value, Key>, Args...>;

    /*!
    * @brief Inserting a copy of the passed value into the table
    * @param p Iterator, after which a new element will be inserted
    * @param mp Values to insert
    * @returns Iterator on the inserted element
    */
    iterator insert(iterator p, const MyPair<Value, Key>& mp)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Inserting the passed value into the table by moving
    * @param p Iterator, after which a new element will be inserted
    * @param mp Values to insert
    * @returns Iterator on the inserted element
    */
    template<typename ... Args>
    iterator insert(iterator p, const MyPair<Value, Key>&& mp)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Inserting n copies of the t value into the table
    * @param p Iterator, after which new elements will be inserted
    * @param n Number of values to insert
    * @param mp Values to insert
    * @returns Iterator on the last inserted element
    */
    iterator insert(iterator p, size_type n, const MyPair<Value, Key>& mp)
        requires std::copy_constructible<MyPair<Value, Key>>;
  
    /*!
    * @brief Inserting into the table of elements from the range [i, j)
    * @param p Iterator after which new elements will be inserted
    * @param i The beginning of the range
    * @param j End of Range
    * @returns Iterator on the last inserted element
    */
    template<std::input_iterator It>
    iterator insert(iterator p, It i, It j)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Inserting items from the initialization list into the table
    * @param p Iterator, after which new elements will be inserted
    * @param il Initialization list to insert
    * @returns Iterator on the last inserted element
    */
    iterator insert(iterator p,std::initializer_list<MyPair<Value, Key>> il)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Deleting an item from the table
    * @param q Iterator, addressable element to delete
    * @returns Iterator to the element that was immediately after the deleted one
    */
    iterator erase(const_iterator q) noexcept;

    /*!
    * @brief Removing items from the table in the range [q1, q2)
    * @param q1 The beginning of the range
    * @param q2 End of Range
    * @returns Iterator to the element that was immediately after the last deleted one
    */
    iterator erase(const_iterator q1, const_iterator q2) noexcept;

    /*!
    * @brief deleting an item by key
    * @param k the key of the item being deleted
    * @returns Iterator to the element that was immediately after the last deleted one
    */
    iterator erase(const Key& k) noexcept;

    /*!
    * @brief Removing all items from the table
    */
    void clear() noexcept;

    /*!
    * @brief Replacing table values with elements from the range [i, j)
    * @param i The beginning of the range
    * @param j End of Range
    */
    template<std::forward_iterator It>
    void assign(It i, It j)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Replacing table values with items from the initialization list
    * @param il Initialization list to insert
    */
    void assign(std::initializer_list<MyPair<Value, Key>> il)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Replacing the table values with n copies of the t value
    * @param n Number of values to insert
    * @param mp Values to insert
    */
    void assign(size_type n, const MyPair<Value, Key>& mp)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
    * @brief Getting the first value in the table
    * @returns Link to the first value from the table
    */
    reference front();

    /*!
    * @brief Getting the first value in the table
    * @returns A constant reference to the first value from the table
    */
    const_reference front() const;

    /*!
    * @brief Getting the last value in the table
    * @returns Link to the last value from the table
    */
    reference back();

    /*!
    * @brief Getting the last value in the table
    * @returns Constant reference to the last value from the table
    */
    const_reference back() const;

    /*!
    * @brief Inserting an element constructed at the beginning of the table
            * from the transmitted values
    * @param args Values to pass to the element constructor
    */
    template<typename ... Args>
    void emplace_front(Args ... args)
        requires std::constructible_from<MyPair<Value, Key>, Args...>;

    /*!
*   * @brief Inserting a copy of the passed value to the top of the TABLE
    * @param mp Values to insert
    */
    void push_front(const MyPair<Value, Key>& mp)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
*   * @brief Inserting the passed value to the top of the TABLE by moving
    * @param mp Values to insert
    */
    void push_front(MyPair<Value, Key>&& mp)
        requires std::copy_constructible<MyPair<Value, Key>>;

    /*!
*   @brief Deleting the first item from the table
    */
    void pop_front() noexcept;

    /*!
    * @brief searching for an item by key
    * @param k the key of the element
    * @returns Iterator per search element
            * if the end() element is missing
    */
    const_iterator find(const Key& k) const noexcept;

    /*!
    * @brief compares elements by key
    * @param n1 the first element
    * @param n2 the second element
    * @returns true if the key of the first one is less
            * false otherwise
    */
    bool key_comp(const MyPair<Value, Key>& n1, const MyPair<Value, Key>& n2) const noexcept;
    
    /*!
    * @brief compares elements by value
    * @param n1 the first element
    * @param n2 the second element
    * @returns true if the value of the first one is less
            * false otherwise
    */
    bool value_comp(const MyPair<Value, Key>& n1, const MyPair<Value, Key>& n2) const noexcept;

private:
    typedef Node<MyPair<Value, Key>> node_t;
    //the first node
    node_t* head = nullptr;
    //table size
    size_t table_size = 0;

    template<typename ...Args>
    node_t* allocate(Args ... args);


    void deallocate(node_t* node) noexcept;
    // Inserting a node into a table
    void insert_node(node_t* val) noexcept;
    // Removing a node from the table
    void erase_node(node_t* val) noexcept;
};

static_assert(std::forward_iterator<TableIterator<int, int, false>>);
static_assert(std::forward_iterator<TableIterator<int, int, true>>);


template<std::default_initializable Value, std::default_initializable Key, bool is_const>
TableIterator<Value, Key, is_const>::TableIterator() noexcept: node(nullptr) {}

template<std::default_initializable Value, std::default_initializable Key, bool is_const>
template<bool other_const>
TableIterator<Value, Key, is_const>::TableIterator(const TableIterator<Value, Key, other_const>& o) noexcept
    requires (is_const >= other_const):
    node(o.node) {}

template<std::default_initializable Value, std::default_initializable Key, bool is_const>
template<bool other_const>
TableIterator<Value, Key, is_const>& TableIterator<Value, Key, is_const>::operator = (const TableIterator<Value, Key, other_const>& o) noexcept
    requires (is_const >= other_const) {
    node = o.node;
    return *this;
}

template<std::default_initializable Value, std::default_initializable Key, bool is_const>
typename TableIterator<Value, Key, is_const>::reference TableIterator<Value, Key, is_const>::operator * () const noexcept {
    return (*this->node).node;
}

template<std::default_initializable Value, std::default_initializable Key, bool is_const>
TableIterator<Value, Key, is_const>::pointer TableIterator<Value, Key, is_const>::operator -> () const noexcept {
    return &node->node;
}

template<std::default_initializable Value, std::default_initializable Key, bool is_const>
template<bool other_const>
bool TableIterator<Value, Key, is_const>::operator == (const TableIterator<Value, Key, other_const>& o) const noexcept {
    return node == o.node;
}

template<std::default_initializable Value, std::default_initializable Key, bool is_const>
TableIterator<Value, Key, is_const>& TableIterator<Value, Key, is_const>::operator ++ () noexcept {
    node = node->next;
    return *this;
}

template<std::default_initializable Value, std::default_initializable Key, bool is_const>
TableIterator<Value, Key, is_const> TableIterator<Value, Key, is_const>::operator ++ (int) noexcept {
    TableIterator res(node);
    node = node->next;
    return res;
}

template<std::default_initializable Value, std::default_initializable Key, bool is_const>
TableIterator<Value, Key, is_const>::TableIterator(node_ptr_t node) :
    node(node) {}






template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::Table()
noexcept (std::is_nothrow_default_constructible_v<MyPair<Value, Key>>) :
    head(nullptr)
{}


template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::Table(const Table& o)
    requires std::copy_constructible<MyPair<Value, Key>>: Table(){
    insert(begin(), o.cbegin(), o.cend());
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::Table(Table&& o)
noexcept(std::is_nothrow_default_constructible_v<MyPair<Value, Key>>) : Table(){
    swap(o);
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::Table(size_type n, const MyPair<Value, Key>& mp)
    requires std::copy_constructible<MyPair<Value, Key>>: Table(){
    insert(begin(), n, mp);
}

template<std::default_initializable Value, std::default_initializable Key>
template <std::input_iterator It>
Table<Value, Key>::Table(It i, It j)
    requires std::constructible_from<MyPair<Value, Key>, std::iter_reference_t<It>> : Table(){
    insert(begin(), i, j);
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::Table(std::initializer_list<MyPair<Value, Key>> il)
    requires std::copy_constructible<MyPair<Value, Key>>: Table(){
    insert(begin(), std::move(il));
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>& Table<Value, Key>::operator = (const Table& o)
    requires std::copy_constructible<MyPair<Value, Key>>{
    if (this == &o)
        return *this;
    assign(o.cbegin(), o.cend());
    return *this;
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>& Table<Value, Key>::operator = (Table&& o) noexcept{
    swap(o);
    return *this;
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::~Table() {
    clear();
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::iterator Table<Value, Key>::begin() noexcept {
    return iterator(head);
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::iterator Table<Value, Key>::end() noexcept {
    return iterator(nullptr);
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::const_iterator Table<Value, Key>::begin() const noexcept {
    return const_iterator(head);
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::const_iterator Table<Value, Key>::end() const noexcept {
    return const_iterator(nullptr);
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::const_iterator Table<Value, Key>::cbegin() const noexcept {
    return const_iterator(head);
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::const_iterator Table<Value, Key>::cend() const noexcept {
    return const_iterator(nullptr);
}

template<std::default_initializable Value, std::default_initializable Key>
bool Table<Value, Key>::operator == (const Table& o) const {
    return table_size == o.table_size &&
        std::equal(begin(), end(),
            o.begin(), o.end());
}

template<std::default_initializable Value, std::default_initializable Key>
void Table<Value, Key>::swap(Table& o) noexcept {
    std::swap(head, o.head);
    std::swap(table_size, o.table_size);
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::size_type Table<Value, Key>::size() const noexcept {
    return table_size;
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::size_type Table<Value, Key>::max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
}

template<std::default_initializable Value, std::default_initializable Key>
bool Table<Value, Key>::empty() const noexcept {
    return table_size == 0;
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>& Table<Value, Key>::operator = (std::initializer_list<MyPair<Value, Key>> il)
    requires std::copy_constructible<MyPair<Value, Key>>{
    assign(std::move(il));
    return *this;
}

template<std::default_initializable Value, std::default_initializable Key>
template<typename ... Args>
Table<Value, Key>::iterator Table<Value, Key>::emplace(iterator p, Args && ... args)
    requires std::constructible_from<MyPair<Value, Key>, Args...>{
    node_t* node = allocate(std::forward<Args>(args)...);
    insert_node(node);
    return iterator(node);
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::iterator Table<Value, Key>::insert(iterator p, const MyPair<Value, Key>& mp)
    requires std::copy_constructible<MyPair<Value, Key>>{
    return emplace(p, mp);
}

template<std::default_initializable Value, std::default_initializable Key>
template<typename ... Args>
Table<Value, Key>::iterator Table<Value, Key>::insert(iterator p, const MyPair<Value, Key>&& mp)
    requires std::copy_constructible<MyPair<Value, Key>>{
    return emplace(p, std::move(mp));
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::iterator Table<Value, Key>::insert(iterator p, size_type n, const MyPair<Value, Key>& mp)
    requires std::copy_constructible<MyPair<Value, Key>>{
    if (n == 0) {
        return iterator(const_cast<node_t*>(p.node));
    }
    iterator prev(p);
    try {
        for (size_t i = 0; i < n; ++i) {
            insert(p, mp);
        }
    }
    catch (...) {
        erase(++prev, p);
        throw;
    }
    return iterator(p);
}

template<std::default_initializable Value, std::default_initializable Key>
template<std::input_iterator It>
Table<Value, Key>::iterator Table<Value, Key>::insert(iterator p, It i, It j)
    requires std::copy_constructible<MyPair<Value, Key>>{
    if (i == j) {
        return iterator(const_cast<node_t*>(p.node));
    }
    iterator prev = iterator(const_cast<node_t*>(p.node));
    try {
        for (; i != j; ++i) {
            p = begin();
            insert(p, *i);
        }
    }
    catch (...) {
        erase(++prev, p);
        throw;
    }
    return iterator(const_cast<node_t*>(p.node));
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::iterator Table<Value, Key>::insert(iterator p, std::initializer_list<MyPair<Value, Key>> il)
    requires std::copy_constructible<MyPair<Value, Key>>{
    return insert(p, std::move_iterator(il.begin()), std::move_iterator(il.end()));
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::iterator Table<Value, Key>::erase(const_iterator q) noexcept{
    node_t* node = const_cast<node_t*>(q.node);
    iterator next = iterator(node->next);
    erase_node(node);
    return next;
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::iterator Table<Value, Key>::erase(const_iterator q1, const_iterator q2) noexcept{
    while (q1 != q2) {
        q1 = erase(q1);
    }
    return iterator(const_cast<node_t*>(q2.node));
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::iterator Table<Value, Key>::erase(const Key& k) noexcept {
    const_iterator it = find(k);
    if (it == end()) return end();

    const_iterator res = erase(it);
    return iterator(const_cast<node_t*>(res.node));
}

template<std::default_initializable Value, std::default_initializable Key>
void Table<Value, Key>::clear() noexcept {
    erase(begin(), end());
}

template<std::default_initializable Value, std::default_initializable Key>
template<std::forward_iterator It>
void Table<Value, Key>::assign(It i, It j)
    requires std::copy_constructible<MyPair<Value, Key>>{
    if (empty()) {
        insert(begin(), i, j);
        return;
    }
    auto first = cbegin();
    auto last = cend();
    erase(first, last);
    insert(begin(), i, j);
}

template<std::default_initializable Value, std::default_initializable Key>
void Table<Value, Key>::assign(std::initializer_list<MyPair<Value, Key>> il)
    requires std::copy_constructible<MyPair<Value, Key>>{
    if (empty()) {
        insert(begin(), std::move(il));
        return;
    }
    auto first = cbegin();
    auto last = cend();
    erase(first, last);
    insert(begin(), std::move(il));
}

template<std::default_initializable Value, std::default_initializable Key>
void Table<Value, Key>::assign(size_type n, const MyPair<Value, Key>& mp)
    requires std::copy_constructible<MyPair<Value, Key>>{
    if (empty()) {
        insert(begin(), n, mp);
        return;
    }
    auto first = cbegin();
    auto last = cend();
    erase(first, last);
    insert(begin(), n, mp);
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::reference Table<Value, Key>::front(){
    return head->node;
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::const_reference Table<Value, Key>::front() const{
    return head->node;
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::reference Table<Value, Key>::back(){
    node_t* last = head;
    while (last->next != nullptr) {
        last = last->next;
    }
    return last->node;
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::const_reference Table<Value, Key>::back() const{
    node_t* last = head;
    while (last->next != nullptr) {
        last = last->next;
    }
    return last->node;
}

template<std::default_initializable Value, std::default_initializable Key>
bool Table<Value, Key>::key_comp(const MyPair<Value, Key>& n1, const MyPair<Value, Key>& n2) const noexcept {
    return n1.key < n2.key;
}

template<std::default_initializable Value, std::default_initializable Key>
bool Table<Value, Key>::value_comp(const MyPair<Value, Key>& n1, const MyPair<Value, Key>& n2) const noexcept {
    return n1.value < n2.value;
}

template<std::default_initializable Value, std::default_initializable Key>
template<typename ... Args>
void Table<Value, Key>::emplace_front(Args ... args)
    requires std::constructible_from<MyPair<Value, Key>, Args...>{
    emplace(begin(), std::forward<Args>(args)...);
}

template<std::default_initializable Value, std::default_initializable Key>
void Table<Value, Key>::push_front(const MyPair<Value, Key>& mp)
    requires std::copy_constructible<MyPair<Value, Key>>{
    insert(begin(), mp);
}

template<std::default_initializable Value, std::default_initializable Key>
void Table<Value, Key>::push_front(MyPair<Value, Key>&& mp)
    requires std::copy_constructible<MyPair<Value, Key>>{
    insert(begin(), std::move(mp));
}

template<std::default_initializable Value, std::default_initializable Key>
void Table<Value, Key>::pop_front() noexcept {
    erase(begin());
}

template<std::default_initializable Value, std::default_initializable Key>
template<typename ...Args>
Table<Value, Key>::node_t* Table<Value, Key>::allocate(Args ... args) {
    return new node_t{ .node = node_type(std::forward<Args>(args)...) };
}

template<std::default_initializable Value, std::default_initializable Key>
void Table<Value, Key>::deallocate(node_t* node) noexcept {
    delete node;
}

template<std::default_initializable Value, std::default_initializable Key>
void Table<Value, Key>::insert_node(node_t* val) noexcept {
    if (find(val->node.key) != end()) {
        deallocate(val);
        return;
    }
    if (head == nullptr) {
        head = val;
    }else {
        node_t* item = head;
        head = val;
        head->next = item;
    }
    ++table_size;
}

template<std::default_initializable Value, std::default_initializable Key>
void Table<Value, Key>::erase_node(node_t* val) noexcept {
    if (table_size == 0) {
        return;
    }
    if (val == head) {
        head = head->next;
        deallocate(val);
        val = nullptr;
    }else if (val->next == nullptr) {
        deallocate(val);
        val = nullptr;
    }else {
        node_t* item = val->next;
        val->node = item->node;
        val->next = item->next;
        deallocate(item);
        item = nullptr;
    }
    --table_size;
}

template<std::default_initializable Value, std::default_initializable Key>
Table<Value, Key>::const_iterator Table<Value, Key>::find(const Key& k) const noexcept {
    node_t* item = head;
    while (item != nullptr) {
        if (item->node.key == k) {
            return const_iterator(item);
        }
        item = item->next;
    }
    return end();
}
#endif // TABLE_H