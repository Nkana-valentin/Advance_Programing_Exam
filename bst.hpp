/*!
 *Lecturer Dr. Alberto Sartori
 * \author Valentin Nkana
 * \date July 2021
 * \mainpage Binary Search Tree
 * \section Introduction
 *  This project was implemented as a final exam for C++ in the course of Advanced Programming.
 * \section Compilation
 * The compilation of the files is done by running the 'make' command; 
 * use the command 'make clean' to remove object files and executables.
 * The executable 'benchmark.x' requires an argument from command line 
 * representing the number of nodes in the tree and std::map : e.g we can run './benchmark.o 50' 
 * will run the tests for a tree and std::map with 50 nodes of (random int keys and int values). 
 * The corresponding output will be three sets of 11 time measurements for the find() 
 * method (for unbalanced tree, balanced tree, std::map each).
 
 
 */

#ifndef __BST_HPP
#define __BST_HPP

#include <iostream>
#include <algorithm>  //swap, sort
#include <utility>    //move, pair
#include <iterator>   // iterators
#include <memory>     // unique_ptr
#include <functional> // std::less
#include <vector>

/// Definition and declaration of the object Node
template <typename K, typename V>
struct Node
{
    std::unique_ptr<Node> _left;
    std::unique_ptr<Node> _right;
    Node *_parent;
    std::pair<const K, V> _data;

    // copy constructor

    Node(const std::pair<const K, V> &data, Node<K, V> *left, Node<K, V> *right, Node<K, V> *parent) noexcept : _left{left}, _right{right}, _parent{parent}, _data{data} {}

    explicit Node(const std::pair<const K, V> &data) noexcept : _left{}, _right{}, _parent{}, _data{data} {}

    Node(const std::pair<const K, V> &data, Node<K, V> *parent) noexcept : _left{}, _right{}, _parent{parent}, _data{data} {}

    Node() = default;

    // move assignment constructor
    Node(std::pair<const K, V> &&data, Node<K, V> *left, Node<K, V> *right, Node<K, V> *parent) noexcept : _left{left}, _right{right}, _parent{parent}, _data{std::move(data)} {}

    Node(std::pair<const K, V> &&data) noexcept : _left{nullptr}, _right{nullptr}, _parent{nullptr}, _data{std::move(data)} {}

    ~Node() = default;

    Node(std::pair<const K, V> &&data, Node<K, V> *parent) noexcept : _left{nullptr}, _right{nullptr}, _parent{parent}, _data{std::move(data)} {}

    Node(const std::unique_ptr<Node<K, V>> &pn, Node<K, V> *parent) : _left{nullptr}, _right{nullptr}, _parent{parent}, _data{pn->_data}
    {

        if (pn->_left)
        {
            _left = std::make_unique<Node>(pn->_left, this);
            // make_unique is carefully implemented
            //for exception safety and is recommended over directly calling unique_ptr constructors.
            //_left->_parent = this;
        }
        if (pn->_right)
        {
            _right = std::make_unique<Node>(pn->_right, this);
            //_right->_parent = this;
        }
    }
    const K key() noexcept { return _data.first; }
    V value() noexcept { return _data.second; }

    void to_print()
    {

        std::cout << "Node has value: " << _data.second << "\n";
        if (_left)
        {
            std::cout << "Left child has value: " << _left->_data.second << "\n";
        }
        if (_right)
        {
            std::cout << "Right child has value: " << _right->_data.second << "\n";
        }
        if (_parent)
        {
            std::cout << "Parent is Node with value: " << _parent->_data.second << "\n";
        }
    }
};
// end of the struct Node declaration and definition

/// declaration of the members and methods of bst class
template <typename K, typename V, typename C = std::less<K>>
class bst
{
private:
    std::unique_ptr<Node<K, V>> _root;
    C comp = C();

    void fill_tree(std::vector<std::pair<const K, V>> &vec, int begin, int end);

    int get_height(Node<K, V> *ptn)
    {

        if (!ptn)
            return 0;

        return 1 + std::max(get_height(ptn->_left.get()), get_height(ptn->_right.get()));
    }

    bool balance_tree_check(Node<K, V> *root_node)
    {

        if (!root_node)
            return true; // the empty tree is a balanced tree by definition;

        int left_height{get_height(root_node->_left.get())};
        int right_height{get_height(root_node->_right.get())};

        if (std::abs(left_height - right_height) <= 1 && balance_tree_check(root_node->_left.get()) && balance_tree_check(root_node->_right.get()))
            return true;

        return false;
    }

public:
    bst() : _root{nullptr} {}

    bst(bst &&tree) noexcept : comp{std::move(tree.comp)}, _root{std::move(tree._root)} {}

    bst &operator=(bst &&tree) noexcept
    {

        comp = std::move(tree.comp);
        _root = std::move(tree._root);

        return *this;
    }

    // copy constructor
    explicit bst(const bst &tree) : comp{tree.comp}
    {
        if (tree._root)
            _root = std::make_unique<Node<K, V>>(tree._root, nullptr); // make_unique for exception safety

        //_root = std::unique_ptr<Node<K, V>>(new Node<K, V>(tree._root, nullptr));
    }

    bst &operator=(bst &tree)
    {
        _root.reset();
        auto tmp{tree};
        *this = std::move(tmp);
        return *this;
    }

    Node<K, V> *root() noexcept { return _root.get(); }

    void clear() noexcept // to destroy the object currently managed by the unique_ptr(if any) and takes the ownership of p.
    {
        // if p is a nullptr pointer (such as a default-initialized pointer), the unique_ptr becomes empty, managing no  object after the call.
        _root.reset();
    }

    void erase(const K &x)
    {
        auto it{find(x)};
        Node<K, V> *loc{it.current};
        if (!(it).current)
            throw("Couldn't find the a Node with the key = x");

        if (loc == _root.get())
        {

            if (!loc->_right && !loc->_left)
            {

                // no child in this case
                _root.reset(nullptr);
            }
            else if (!(!loc->_left) != !(!loc->_right))
            {

                // one child in this case
                if (loc->_right)
                {

                    // child is the right one
                    _root.reset(loc->_right.release());
                    loc->_left->_parent = nullptr;
                }
                else
                {

                    // child is the left one
                    _root.reset(loc->_left.release());
                    loc->_left->_parent = nullptr;
                }
            }
            else
            {

                // two children in this case
                auto succ = (++it).current;
                auto DN = std::unique_ptr<Node<K, V>>(new Node<K, V>(succ->_data, nullptr));
                DN->_left.reset(loc->_left.release());
                DN->_left->_parent = DN.get();
                if (succ == loc->_right.get())
                {

                    DN->_right.reset(succ->_right.release());
                    if (DN->_right)
                    {

                        // if succ has a right child
                        DN->_right->_parent = DN.get();
                    }
                }
                else
                {

                    // succ is not the next one
                    DN->_right.reset(loc->_right.release());
                    DN->_right->_parent = DN.get();
                    if (succ->_right)
                    {

                        // succ has right child
                        succ->_right->_parent = succ->_parent;
                        succ->_parent->_left.reset(succ->_right.release());
                    }
                    else
                    {

                        // succ is a leaf
                        succ->_parent->_left.reset();
                    }
                }
                _root.reset(DN.release());
            }
        }
        else
        {

            // the node to be deleted is not the _root
            if (!(loc->_left) && !(loc->_right))
            {

                if (loc == loc->_parent->_left.get())
                {

                    loc->_parent->_left.reset();
                }
                else
                {

                    loc->_parent->_right.reset();
                }
            }
            else if (!(!loc->_left) != !(!loc->_right))
            {

                if (loc->_left)
                {

                    loc->_left->_parent = loc->_parent;
                    if (loc == loc->_parent->_left.get())
                    {

                        loc->_parent->_left.reset(loc->_left.release());
                    }
                    else
                    {

                        loc->_parent->_right.reset(loc->_left.release());
                    }
                }
                else
                {

                    loc->_right->_parent = loc->_parent;
                    if (loc == loc->_parent->_left.get())
                    {

                        loc->_parent->_left.reset(loc->_right.release());
                    }
                    else
                    {

                        loc->_parent->_right.reset(loc->_right.release());
                    }
                }
            }
            else
            {

                ++it;
                Node<K, V> *succ{it.current};

                if (succ != loc->_right.get())
                {

                    auto DNP{loc->_parent};
                    auto DN{std::unique_ptr<Node<K, V>>(new Node<K, V>(succ->_data, DNP))};
                    erase(succ->_data.first);

                    DN->_left.reset(loc->_left.release());
                    DN->_left->_parent = DN.get();
                    DN->_right.reset(loc->_right.release());
                    DN->_right->_parent = DN.get();

                    if (loc == DNP->_left.get())
                    {

                        DNP->_left.reset(DN.release());
                    }
                    else
                    {

                        DNP->_right.reset(DN.release());
                    }
                }
                else
                {

                    succ->_left.reset(loc->_left.release());
                    succ->_left->_parent = succ;
                    erase(loc->_data.first);
                }
            }
        }
    }

    template <typename T>
    V &operator[](T &&key);

    template <typename O>
    class __iterator;

    using iterator = __iterator<std::pair<const K, V>>;
    using const_iterator = __iterator<const std::pair<const K, V>>;

    iterator begin() noexcept
    {
        auto p = _root.get();
        if (!p)
            return iterator(p);

        while (p->_left)
        {                         // p->_left access requires p!=nullptr or segmentation fault
            p = (p->_left).get(); // would otherwise dereference nullptr
        }
        return iterator{p};
    }
    iterator end() noexcept
    {
        return iterator{nullptr};
    }

    const_iterator begin() const noexcept
    {
        auto p = _root.get();
        if (!p)
            return const_iterator(p);
        while (p->_left)
            p = (p->_left).get();
        return const_iterator{p};
    }

    const_iterator end() const noexcept
    {
        return const_iterator{nullptr};
    }

    const_iterator cbegin() const noexcept
    {
        auto p = _root.get();
        if (!p)
            return const_iterator(p);
        while (p->_left)
        {
            p = (p->_left).get();
        }
        return const_iterator{p};
    }

    const_iterator cend() const noexcept
    {
        return const_iterator{nullptr};
    }

    iterator find(const K &key);

    const_iterator find(const K &key) const;

    std::pair<iterator, bool> insert(const std::pair<const K, V> &data);

    std::pair<iterator, bool> insert(std::pair<const K, V> &&data);

    template <typename... Types>
    std::pair<iterator, bool> emplace(Types &&...args);

    friend std::ostream &operator<<(std::ostream &os, const bst &tree)
    {
        for (const auto it : tree)
            os << it.first << " ";
        return os;
    }

    void balance();

    bool is_balanced()
    {

        return balance_tree_check(_root.get());
    }
}; // end of the  bst class declaration

// Begin of the definition the members of the class bst
template <typename K, typename V, typename C>
void bst<K, V, C>::fill_tree(std::vector<std::pair<const K, V>> &vec, int begin, int end)
{

    insert(vec[static_cast<int>((begin + end) / 2)]); // performing a static cast operation.

    if (begin >= end)
        return;

    fill_tree(vec, begin, (begin + end) / 2 - 1);
    fill_tree(vec, (begin + end) / 2 + 1, end);
}

template <typename K, typename V, typename C>
void bst<K, V, C>::balance()
{
    if (!_root)
        return;

    std::vector<std::pair<const K, V>> temp_vec{}; // define a temporary vector of key-value
    for (auto it = begin(); it != end(); ++it)
        temp_vec.push_back(*it);

    clear(); // destroy all the elements of temp_vec and sets size equal to zero

    fill_tree(temp_vec, 0, temp_vec.size() - 1);
}

template <typename K, typename V, typename C>
typename bst<K, V, C>::iterator bst<K, V, C>::find(const K &key)
{

    auto p = _root.get();
    bool go_left;
    bool go_right;

    while (p)
    {
        go_right = comp(p->_data.first, key);
        go_left = comp(key, p->_data.first);

        if (go_right)
            p = (p->_right).get();
        else if (go_left)
            p = (p->_left).get();
        else
            return iterator(p);
    }

    return end();
}
/// To find an node inside the binary tree
template <typename K, typename V, typename C>
typename bst<K, V, C>::const_iterator bst<K, V, C>::find(const K &key) const
{

    auto p = _root.get();
    bool go_left;
    bool go_right;

    while (p)
    {

        go_right = comp(p->_data.first, key);
        go_left = comp(key, p->_data.first);

        if (go_right)
            p = (p->_right).get();
        else if (go_left)
            p = (p->_left).get();
        else
            return iterator(p);
    }
    return end();
}

/// To insert a node inside the bst first version
template <typename K, typename V, typename C>
std::pair<typename bst<K, V, C>::iterator, bool> bst<K, V, C>::insert(const std::pair<const K, V> &data)
{

    if (_root == nullptr)
    {
        _root.reset(new Node<K, V>{data, nullptr});
        return std::make_pair(iterator(_root.get()), true);
    }
    auto p = _root.get();
    bool go_left;
    bool go_right;

    while (true)
    {

        go_right = comp(p->_data.first, data.first);
        go_left = comp(data.first, p->_data.first);
        if (go_right)
        {
            if (p->_right)
                p = (p->_right).get();
            else
            {

                p->_right.reset(new Node<K, V>{data, p});
                return std::make_pair(iterator(p->_right.get()), true);
            }
        }
        else if (go_left)
        {
            if (p->_left)
                p = (p->_left).get();
            else
            {
                p->_left.reset(new Node<K, V>{data, p});
                return std::make_pair(iterator(p->_left.get()), true);
            }
        }
        else
            return std::make_pair(iterator(p), false);
    }
}
//// R-value insert
template <typename K, typename V, typename C>
std::pair<typename bst<K, V, C>::iterator, bool> bst<K, V, C>::insert(std::pair<const K, V> &&data)
{
    if (_root == nullptr)
    {
        _root.reset(new Node<K, V>{std::move(data), nullptr});
        return std::make_pair(iterator(_root.get()), true);
    }
    auto p = _root.get();

    bool go_left;
    bool go_right;

    while (true)
    {
        go_right = comp(p->_data.first, data.first);
        go_left = comp(data.first, p->_data.first);

        if (go_right)
        {

            if (p->_right)

                p = (p->_right).get();

            else
            {

                p->_right.reset(new Node<K, V>{std::move(data), p});
                return std::make_pair(iterator(p->_right.get()), true);
            }
        }

        else if (go_left)
        {

            if (p->_left)

                p = (p->_left).get();

            else
            {

                p->_left.reset(new Node<K, V>{std::move(data), p});
                return std::make_pair(iterator(p->_left.get()), true);
            }
        }
        else
            return std::make_pair(iterator(p), false);
    }
}

/// definition of the emplace method

template <typename K, typename V, typename C>
template <typename... Types>
std::pair<typename bst<K, V, C>::iterator, bool> bst<K, V, C>::emplace(Types &&...args)
{

    return insert(std::pair<const K, V>{std::forward<Types>(args)...});
}

/// Overloadding of the operator []
template <typename K, typename V, typename C>
template <typename T>
V &bst<K, V, C>::operator[](T &&key)
{

    auto p = find(std::forward<T>(key));

    if (p != end())
        return p->second;
    else
    {

        p = insert({std::forward<T>(key), V{}}).first;
        return p->second;
    }
}

/// Iterator definition of the class bst:
//are used to reduced the complexity and the execution time of a program.

template <typename K, typename V, typename C>
template <typename O>
class bst<K, V, C>::__iterator
{
private:
    Node<K, V> *current;
    //Node<K, V> current;

public:
    /**
     * @brief Custom constructor for @ref iterator
     * @param x Raw pointer to a @ref Node
     *
     * Construct a new @ref __iterator that refers to @ref Node x
     */
    explicit __iterator(Node<K, V> *x) noexcept : current{x} {}

    friend class bst;
    using value_type = O; // the typename of the iterator
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type &;
    using pointer = value_type *;

    /**
     * @brief Default-generated constructor
     *
     */
    __iterator() noexcept = default;

    /**
     * @brief Default-generated destructor
     *
     */
    ~__iterator() = default;

    /**
     * @brief Dereference operator
     *
     * Dereferences an @ref __iterator by returning the data stored by the @ref Node it refers to
     */
    reference operator*() const noexcept { return current->_data; } // return 0 reference

    pointer operator->() const noexcept { return &(*(*this)); }

    friend bool operator==(const __iterator &a, const __iterator &b)
    {

        return a.current == b.current;
    }

    friend bool operator!=(const __iterator &a, const __iterator &b)
    {

        return !(a == b);
    }

    __iterator &operator++() noexcept
    { //pre increment

        auto current_right = current->_right.get();
        auto current_parent = current->_parent;

        if (current_right)
        {

            while (current_right->_left)
                current_right = current_right->_left.get();
            current = current_right;
        }
        else
        {

            while (current_parent && current_parent->_right.get() == current)
            {
                current = current_parent;
                current_parent = current_parent->_parent;
            }
            current = current_parent;
        }
        return *this;
    }
    /**
 * @brief Post increment operator
 * 
 * @return __iterator 
 */
    __iterator operator++(int)
    {

        auto tmp{*this};
        ++(*this);
        return tmp;
    }

    void print_iterator()
    {
        current->to_print();
    }
};

#endif
