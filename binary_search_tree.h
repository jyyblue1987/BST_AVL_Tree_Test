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
    Node<Comparable>* insertNode(BinarySearchTree<Comparable>* root, Comparable& v);
    void make_empty();
    void freeNodeTree(Node<Comparable>* node);
    void copy(Node<Comparable>* node);
    bool searchNode(Node<Comparable>* root, Comparable v);
    Node<Comparable>* deleteNode(Node<Comparable>* root, Comparable v);
    void print(Node<Comparable>* root, int depth, std::ostream& out=std::cout);

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
    void print_tree(std::ostream& out=std::cout) const;
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
}

template <typename Comparable>
void BinarySearchTree<Comparable>::make_empty() {
	freeNodeTree(root);
	root = NULL;

	return true;
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

	insertNode(root, node->data);
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
bool BinarySearchTree<Comparable>::searchNode(Node<Comparable>* root, Comparable v){
	if(root == NULL){
		return false;
	}else if(root->data == v){
		return true;
	}else if(v <= root->data){
		return searchNode(root->left, v);
	}else{
		return searchNode(root->right, v);
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
Node<Comparable>* BinarySearchTree<Comparable>::insertNode(BinarySearchTree<Comparable>* root, Comparable& v){
	if(root == NULL){
		root = getNewNode(v);
	}else if(v <= root->data){
		root->left = insertNode(root->left, v);
	}else{
		root->right = insertNode(root->right, v);
	}
	return root;
} 

// Insert a Node
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& v)
{
	insertNode(root, v);
} 

// Delete a Node
template <typename Comparable>
Node<Comparable>* BinarySearchTree<Comparable>::deleteNode(Node<Comparable>* root, Comparable v){
	if(root == NULL) return root;
	else if(v < root->data) root->left = deleteNode(root->left, v);
	else if(v > root->data) root->right = deleteNode(root->right, v);
	else{
		if(root->left == NULL && root->right == NULL){
			delete root;
			root = NULL;
		}else if(root->left == NULL){
			Node<Comparable>* temp = root;
			root = root->right;
			delete temp;
		}else if(root->right == NULL){
			Node<Comparable>* temp = root;
			root = root->left;
			delete temp;
		}else{
			// Two Children
			Node<Comparable>* temp = findMin(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right,temp->data);
		}
	}
	return root;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& v)
{
    deleteNode(root, v)
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
void BinarySearchTree<Comparable>::print(Node<Comparable>* node, int depth, std::ostream& out=std::cout)
{
    if(node == NULL) 
        return;
    
    print(root->left, depth + 1, out);

    for(int i = 0; i < depth; i++)
        out << '\t';

    out << node->data << endl;

    print(root->right, depth + 1, out);
}


template <typename Comparable>
void BinarySearchTree<Comparable>::print_tree(std::ostream& out=std::cout) const
{
    print(root, 0);
    
}


#endif