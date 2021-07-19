#include "bst.hpp"
//#include "tree.hpp"
#include <cstdlib> // rand
#include <iostream>
#include <ctime>
#include <chrono>
#include <map>

int main()
{
    Node<int, int> mynode{{8, 8}, nullptr};
    bst<int, int> mytree{};
    auto a = mytree.insert({4, 4});
    auto b = mytree.insert({2, 2});
    auto c = mytree.insert({1, 1});
    auto d = mytree.insert({7, 7});
    auto e = mytree.insert({6, 6});
    auto f = mytree.insert({5, 5});
    //mytree.balance();

    //bst<int, int>::Iterator<int> it;

    //for (auto x : tree)
    std::cout << mytree << std::endl;

    //std::cout << mytree.tree_minimum() << std::endl;

    std::pair<int, int> parent_pair{8, 8};
    Node<int, int> parent_node{parent_pair, nullptr};
    std::pair<int, int> elf_pair{11, 11};

    parent_node._right = std::unique_ptr<Node<int, int>>{new Node<int, int>{elf_pair, &parent_node}};

    std::pair<int, int> nine_pair{9, 9};
    std::pair<int, int> ten_pair{10, 10};
    std::pair<int, int> frteen_pair{14, 14};

    parent_node._right->_right = std::unique_ptr<Node<int, int>>{new Node<int, int>{frteen_pair, parent_node._right.get()}};
    parent_node._right->_left = std::unique_ptr<Node<int, int>>{new Node<int, int>{ten_pair, parent_node._right.get()}};
    parent_node._right->_left->_left.reset(new Node<int, int>{nine_pair, parent_node._right->_left.get()});

    parent_node.to_print();
    parent_node._right->to_print();
    parent_node._right->_left->to_print();

    //auto it{__iterator<std::pair<int, int>(&parent_node)};
    bst<int, int>::__iterator<int> it{&parent_node};
    //auto it{__iterator<std::pair<int, int>>(&parent_node)};

    //std::cout << parent_node._left->_data.second << std::endl;
    //std::cout << it.current->to_print() << " ";

    /* auto itpp{++it};
    std::cout << "Expect next node's value: " << nine_pair.second << ". \t"
              << "obtained: " << itpp.print_iterator() << "\n"; */
    /* 
    bst<int, int>::__iterator<int> itp{&parent_node};

    bool is_equal{it == itp};
    bool is_not_equal{it != itp};

    std::cout << "Test for iterators equality: " << is_equal << "\n"
              << "Test for operator not equal: " << is_not_equal << "\n"; */

    std::cout << "Exam tree test: "
              << "\n";

    bst<int, int> my_tree{}; // create an empty tree:  default ctor call to each members
    auto g = my_tree.insert({8, 8});
    auto h = my_tree.insert({3, 3});
    auto i = my_tree.insert({10, 10});
    auto j = my_tree.insert({1, 1});
    auto l = my_tree.insert({6, 6});
    auto m = my_tree.insert({4, 4});
    auto n = my_tree.insert({7, 7});
    auto o = my_tree.insert({14, 14});
    auto n1 = my_tree.insert({13, 13});
    auto m1 = my_tree.insert({4, 4});

    std::cout << "Test with a random-generated tree: "
              << "\n";

    bst<int, int> rand_tree{};

    srand(time(NULL)); // random seed

    int rd_val{};
    for (auto i = 0; i <= 10; ++i)
    {

        rd_val = std::rand() % 100;
        auto it = rand_tree.insert({rd_val, rd_val});
    }

    std::cout << rand_tree << "\n";

    std::cout << "operator put-to: " << my_tree << std::endl;

    auto fd{my_tree.find(8)};

    std::cout << "operator [] test: "
              << "\n";

    int lvalueint{40};
    my_tree[5] = 5;

    my_tree[lvalueint] = lvalueint;
    my_tree.operator[](lvalueint) = lvalueint;

    std::cout << my_tree << "\n";

    std::cout << "Emplace test: "
              << "\n";
    auto ff{my_tree.emplace(80, 80)};
    std::cout << my_tree << "\n";

    std::cout << "Test copy semantics: "
              << "\n";

    std::cout << "deep copy"
              << "\n";

    bst<int, int> test_copy_semantics{rand_tree};
    std::cout << "original: " << rand_tree << "\n"
              << "copied: " << test_copy_semantics << "\n";

    std::cout << "Copy assignment: "
              << "\n";

    test_copy_semantics = my_tree;
    std::cout << "now it is \n"
              << test_copy_semantics << "\n";

    auto ins12 = test_copy_semantics.insert(std::pair<int, int>(12, 12)); // r-value insertion

    std::cout << "to check the deepest copy: \n"
              << test_copy_semantics << "\n and the original is\n " << my_tree << "\n";

    std::cout << "To test the move semantics"
              << "\n";

    std::cout << "move constructor"
              << "\n";

    bst<int, int> test_move_semantics{std::move(my_tree)}; // move ctr

    std::cout << "Original after the move: \n"
              << my_tree << "has been moved to: \n"
              << test_move_semantics << "\n";

    std::cout << "*** Move assignment: ***"
              << "\n";
    std::cout << "Before moving: \n"
              << rand_tree << "\n";

    test_move_semantics = std::move(rand_tree); // the move assignment

    std::cout << "Original after moved: \n"
              << rand_tree << "has been moved to \n"
              << test_move_semantics << "\n";

    std::cout << " Balance test: "
              << "\n";
    bst<int, int> to_balanced{};
    for (auto i = 0; i <= 6; ++i)
        to_balanced.insert({i, i});

    std::cout << to_balanced << "\n";

    to_balanced.balance();

    bool is_bal{to_balanced.is_balanced()};

    std::cout << "Is it balanced? " << is_bal << "\n";

    std::cout << " balance the random tree: "
              << "\n";

    test_move_semantics.balance();

    std::cout << "Is it balanced? " << test_move_semantics.is_balanced() << "\n";

    my_tree.clear();

    rand_tree.clear();

    test_move_semantics.clear();

    test_copy_semantics.clear();

    std::cout << "Find tree minimum: "
              << "\n";

    //Node<int, int> p{}; // create a new node

    //auto itt{my_tree.tree_minimum(my_tree._root->get())};

    //std::cout << to_balanced.tree_minimum(to_balanced._root) << "\n";

    //std::cout << " The value of the iterator" << itt->first << "\n";

    std::cout << "Erase tests: "
              << "\n";
    bst<int, int> erase_test{to_balanced}; // copy constructor call
    std::cout << " Before erasing: " << erase_test << "\n";

    erase_test.erase(4); // the key to be deleted corresponds to the key to the root
    std::cout << "Removed Node with key=4: " << erase_test << "\n";

    bst<int, int> erasure_test2{};
    using intpair = std::pair<int, int>;
    auto er1{erasure_test2.insert(intpair(5, 5))};
    auto er2{erasure_test2.insert(intpair(2, 2))};
    auto er3{erasure_test2.insert(intpair(12, 12))};
    auto er4{erasure_test2.insert(intpair(3, 3))};
    auto er5{erasure_test2.insert(intpair(9, 9))};
    auto er6{erasure_test2.insert(intpair(21, 21))};
    auto er7{erasure_test2.insert(intpair(19, 19))};
    auto er8{erasure_test2.insert(intpair(25, 25))};

    std::cout << "Before erasing: " << erasure_test2 << "\n";
    erasure_test2.erase(12);

    std::cout << "After erasing node with key = 12: " << erasure_test2 << "\n";

    bst<int, int> erasure_test3{};
    auto ert1{erasure_test3.insert(intpair(8, 8))};
    auto ert2{erasure_test3.insert(intpair(6, 6))};
    auto ert3{erasure_test3.insert(intpair(10, 10))};
    auto ert4{erasure_test3.insert(intpair(9, 9))};
    auto ert5{erasure_test3.insert(intpair(11, 11))};
    auto ert6{erasure_test3.insert(intpair(3, 3))};
    auto ert7{erasure_test3.insert(intpair(7, 7))};
    //    auto ert6{erasure_test3.insert(intpair(12,12))};

    try
    {
        erasure_test3.erase(8);
        erasure_test3.erase(60);
    }
    catch (const std::exception &e)
    {

        std::cerr << e.what() << '\n';
        return 1;
    }

    catch (...)
    {

        std::cerr << "Unknown key" << '\n';
    }

    std::cout << "example of another tree where the successor has  a right child with emplace"
              << "\n";
    bst<int, int> tree_for_test{};
    auto test1{tree_for_test.emplace(8, 8)};
    auto test2{tree_for_test.emplace(3, 3)};
    auto test3{tree_for_test.emplace(1, 1)};
    auto test4{tree_for_test.emplace(6, 6)};
    auto test5{tree_for_test.emplace(21, 21)};
    auto test6{tree_for_test.emplace(9, 9)};
    auto test7{tree_for_test.emplace(10, 10)}; // succ of key 9
    std::cout << "The new tree is: " << tree_for_test << "\n";
    std::cout << "Case of two children and successor is not the next one with the right child"
              << "\n";
    tree_for_test.erase(8);

    std::cout << "After removing a key 8 which is the head node: the tree becomes \n"
              << tree_for_test << std::endl;

    rand_tree.clear();
    std::cout << rand_tree << "\n";

    return 0;
    /* bst<int, int>::my_comp<int> cmp;
    //auto bb = cmp.fun(test7 < test5);
    std::cout << cmp.fun(5, 7) << "\n"; */
}