#ifndef AVL_TREE_H
#define AVL_TREE_H

template <typename Comparable>
class AVLTree {
    // TODO: implement AVLTree
public:
	AVLTree() ; // - makes an empty tree
	AVLTree(const AVLTree&); // constructs a copy of the given tree
	~AVLTree(); //  destructs this tree
	AVLTree& operator=(const AVLTree&); //  assigns a copy of the given tree
	bool contains(const Comparable&) const; //  - returns Boolean true if the specified value is in the		tree
	void insert(const Comparable&); //  - insert the given value into the tree
	void remove(const Comparable&); //  - remove the specified value from the tree (use minimum of right child tree when value has two children)
	const Comparable& find_min() const; //  - return the minimum value in the tree or throw std::invalid_argument if the tree is empty
	const Comparable& find_max() const; //  - return the maximum value in the tree or throw std::invalid_argument if the tree is empty
    void print_tree(std::ostream& out=std::cout) const;

};

#endif