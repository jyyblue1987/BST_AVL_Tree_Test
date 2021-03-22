#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
using namespace std;

template <typename Comparable>
class BinarySearchTree {


    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree&);
    ~BinarySearchTree();
    BinarySearchTree& operator=(const BinarySearchTree&);
    bool contains(const Comparable&);
    void insert(const Comparable&);
    void remove(const Comparable&);
    const Comparable& find_min() const:
    const Comparable& find_max() const;
    void print_tree(std::ostream&=std::cout);

};

#endif