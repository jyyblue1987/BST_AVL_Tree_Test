#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iostream>

using namespace std;

template <typename Comparable>
struct Node{
	Comparable data;
	Node<Comparable>* left;
	Node<Comparable>* right;
};


template <typename Comparable>
class BinarySearchTree {
private:
    Node<Comparable>* getNewNode(Comparable& v);
    Node<Comparable>* insertNode(Node<Comparable>* node, Comparable v);
    void make_empty();
    void freeNodeTree(Node<Comparable>* node);
    void copy(Node<Comparable>* node);
    bool searchNode(Node<Comparable>* node, Comparable v);
    Node<Comparable>* deleteNode(Node<Comparable>* node, Comparable v);
    Node<Comparable>* findMin(Node<Comparable>* node);
    void print(Node<Comparable>* node, int depth, std::ostream& out=std::cout);        
protected: 
    Node<Comparable>	*root;

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree&);
    ~BinarySearchTree();
    BinarySearchTree& operator=(const BinarySearchTree&);
    bool contains(const Comparable&);
    void insert(const Comparable&);
    void remove(const Comparable&);
    const Comparable& find_min() const;
    const Comparable& find_max() const;
    void print_tree(std::ostream& out=std::cout);
};

// Default Constructor
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(){
	root = NULL;
}

// Copy Constructor    
template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree& obj) 
{
    // search all trees
    root = NULL;
    copy(obj.root);
}

// Default Destructor
template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree(){
    make_empty();
}

template <typename Comparable>
BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree<Comparable>& obj) 
{
    make_empty();
    copy(obj.root);

    return *this;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::make_empty() {
	freeNodeTree(root);
	root = NULL;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::freeNodeTree(Node<Comparable>* node) {
	if (node != NULL)
	{
		freeNodeTree(node->left);
		freeNodeTree(node->right);

		delete node;
	}
}

// Insert a Node On total tree
template <typename Comparable>
void BinarySearchTree<Comparable>::copy(Node<Comparable>* node)
{
    if( node == NULL )
        return;

	insert(node->data);
    copy(node->left);
    copy(node->right);
} 

// check contain
template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& v)
{
    return searchNode(root, v);
}


// Search a Node
template <typename Comparable>
bool BinarySearchTree<Comparable>::searchNode(Node<Comparable>* node, Comparable v){
	if(node == NULL){
		return false;
	}else if(node->data == v){
		return true;
	}else if(v <= node->data){
		return searchNode(node->left, v);
	}else{
		return searchNode(node->right, v);
	}
}


template <typename Comparable>
Node<Comparable>* BinarySearchTree<Comparable>::getNewNode(Comparable& v){
	Node<Comparable>* temp = new Node<Comparable>();
	temp->data = v;
	temp->left = temp->right = NULL;
	return temp;
}

// Insert a Node
template <typename Comparable>
Node<Comparable>* BinarySearchTree<Comparable>::insertNode(Node<Comparable>* node, Comparable v){
	if(node == NULL){
		node = getNewNode(v);
	}else if(v < node->data){
		node->left = insertNode(node->left, v);
	}else if(v > node->data){
		node->right = insertNode(node->right, v);
	}
	return node;
} 

// Insert a Node
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& v)
{
	root = insertNode(root, v);    
} 

// Delete a Node
template <typename Comparable>
Node<Comparable>* BinarySearchTree<Comparable>::deleteNode(Node<Comparable>* node, Comparable v){
	if(node == NULL) return node;
	else if(v < node->data) node->left = deleteNode(node->left, v);
	else if(v > node->data) node->right = deleteNode(node->right, v);
	else{
		if(node->left == NULL && node->right == NULL){
			delete node;
			node = NULL;
		}else if(node->left == NULL){
			Node<Comparable>* temp = node;
			node = node->right;
			delete temp;
		}else if(node->right == NULL){
			Node<Comparable>* temp = node;
			node = node->left;
			delete temp;
		}else{
			// Two Children
			Node<Comparable>* temp = findMin(node->right);
			node->data = temp->data;
			node->right = deleteNode(node->right,temp->data);
		}
	}
	return node;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& v)
{
    root = deleteNode(root, v);
}

template <typename Comparable>
const Comparable& BinarySearchTree<Comparable>::find_min() const
{
	if( root == NULL )
        throw std::invalid_argument("Invalid argument.");

    Node<Comparable> *node = root;

    while(node->left != NULL) 
        node = node->left;
	
    return node->data;
}
template <typename Comparable>
Node<Comparable>* BinarySearchTree<Comparable>::findMin(Node<Comparable>* node)
{
	while(node->left != NULL) node = node->left;
	return node;
}

template <typename Comparable>
const Comparable& BinarySearchTree<Comparable>::find_max() const
{
	if( root == NULL )
        throw std::invalid_argument("Invalid argument.");

    Node<Comparable> *node = root;

    while(node->right != NULL) 
        node = node->right;
	
    return node->data;
}


// Print the Tree - Pre Order Traversal
template <typename Comparable>
void BinarySearchTree<Comparable>::print(Node<Comparable>* node, int depth, std::ostream& out)
{
    if(node == NULL) 
        return;
    
    print(node->right, depth + 1, out);

    for(int i = 0; i < depth; i++)
        out << "  ";

    out << node->data << endl;

    print(node->left, depth + 1, out);
}


template <typename Comparable>
void BinarySearchTree<Comparable>::print_tree(std::ostream& out)
{
    print(root, 0, out);
    out << endl;    
}


#endif