#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

using namespace std;


template <typename Comparable>
struct AVNode{
	Comparable data;
	AVNode<Comparable>* left;
	AVNode<Comparable>* right;
};

template <typename Comparable>
class AVLTree {
private:
    AVNode<Comparable>* getNewNode(Comparable& v);
    AVNode<Comparable>* insertNode(AVNode<Comparable>* node, Comparable v);
    void make_empty();
    void freeNodeTree(AVNode<Comparable>* node);
    void copy(AVNode<Comparable>* node);
    bool searchNode(AVNode<Comparable>* node, Comparable v);
    AVNode<Comparable>* deleteNode(AVNode<Comparable>* node, Comparable v);
    AVNode<Comparable>* findMin(AVNode<Comparable>* node);
    void print(AVNode<Comparable>* node, int depth, std::ostream& out=std::cout);        

	AVNode<Comparable>* balance(AVNode<Comparable>* );
	int height(AVNode<Comparable>* );
	int diff(AVNode<Comparable>* );
	AVNode<Comparable>* rr_rotation(AVNode<Comparable>* );
	AVNode<Comparable>* ll_rotation(AVNode<Comparable>* );
	AVNode<Comparable>* lr_rotation(AVNode<Comparable>* );
	AVNode<Comparable>* rl_rotation(AVNode<Comparable>* );
	

protected: 
    AVNode<Comparable>	*root;
public:
	AVLTree() ; // - makes an empty tree
	AVLTree(const AVLTree&); // constructs a copy of the given tree
	~AVLTree(); //  destructs this tree
	AVLTree& operator=(const AVLTree&); //  assigns a copy of the given tree
	bool contains(const Comparable&); //  - returns Boolean true if the specified value is in the		tree
	void insert(const Comparable&); //  - insert the given value into the tree
	void remove(const Comparable&); //  - remove the specified value from the tree (use minimum of right child tree when value has two children)
	const Comparable& find_min() const; //  - return the minimum value in the tree or throw std::invalid_argument if the tree is empty
	const Comparable& find_max() const; //  - return the maximum value in the tree or throw std::invalid_argument if the tree is empty
    void print_tree(std::ostream& out=std::cout);

};


// Default Constructor
template <typename Comparable>
AVLTree<Comparable>::AVLTree(){
	root = NULL;
}

// Copy Constructor    
template <typename Comparable>
AVLTree<Comparable>::AVLTree(const AVLTree& obj) 
{
    // search all trees
    root = NULL;
    copy(obj.root);
}

// Default Destructor
template <typename Comparable>
AVLTree<Comparable>::~AVLTree(){
    make_empty();
}

template <typename Comparable>
AVLTree<Comparable>& AVLTree<Comparable>::operator=(const AVLTree<Comparable>& obj) 
{
    make_empty();
    copy(obj.root);

    return *this;
}

template <typename Comparable>
void AVLTree<Comparable>::make_empty() {
	freeNodeTree(root);
	root = NULL;
}

template <typename Comparable>
void AVLTree<Comparable>::freeNodeTree(AVNode<Comparable>* node) {
	if (node != NULL)
	{
		freeNodeTree(node->left);
		freeNodeTree(node->right);

		delete node;
	}
}

// Insert a AVNode On total tree
template <typename Comparable>
void AVLTree<Comparable>::copy(AVNode<Comparable>* node)
{
    if( node == NULL )
        return;

	insert(node->data);
    copy(node->left);
    copy(node->right);
} 

// check contain
template <typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable& v)
{
    return searchNode(root, v);
}


// Search a AVNode
template <typename Comparable>
bool AVLTree<Comparable>::searchNode(AVNode<Comparable>* node, Comparable v){
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
AVNode<Comparable>* AVLTree<Comparable>::getNewNode(Comparable& v){
	AVNode<Comparable>* temp = new AVNode<Comparable>();
	temp->data = v;
	temp->left = temp->right = NULL;
	return temp;
}

// Insert a AVNode
template <typename Comparable>
AVNode<Comparable>* AVLTree<Comparable>::insertNode(AVNode<Comparable>* node, Comparable v){
	if(node == NULL){
		node = getNewNode(v);
	}else if(v <= node->data){
		node->left = insertNode(node->left, v);
		node = balance(node);
	}else{
		node->right = insertNode(node->right, v);
		node = balance(node);
	}
	return node;
} 

// Insert a AVNode
template <typename Comparable>
void AVLTree<Comparable>::insert(const Comparable& v)
{
	root = insertNode(root, v);    
} 

// Delete a AVNode
template <typename Comparable>
AVNode<Comparable>* AVLTree<Comparable>::deleteNode(AVNode<Comparable>* node, Comparable v){
	if(node == NULL) return node;
	else if(v < node->data) node->left = deleteNode(node->left, v);
	else if(v > node->data) node->right = deleteNode(node->right, v);
	else{
		if(node->left == NULL && node->right == NULL){
			delete node;
			node = NULL;
		}else if(node->left == NULL){
			AVNode<Comparable>* temp = node;
			node = node->right;
			delete temp;
		}else if(node->right == NULL){
			AVNode<Comparable>* temp = node;
			node = node->left;
			delete temp;
		}else{
			// Two Children
			AVNode<Comparable>* temp = findMin(node->right);
			node->data = temp->data;
			node->right = deleteNode(node->right,temp->data);
		}
	}
	return node;
}

template <typename Comparable>
void AVLTree<Comparable>::remove(const Comparable& v)
{
    deleteNode(root, v);
}

template <typename Comparable>
const Comparable& AVLTree<Comparable>::find_min() const
{
	if( root == NULL )
        throw std::invalid_argument("Invalid argument.");

    AVNode<Comparable> *node = root;

    while(node->left != NULL) 
        node = node->left;
	
    return node->data;
}
template <typename Comparable>
AVNode<Comparable>* AVLTree<Comparable>::findMin(AVNode<Comparable>* node)
{
	while(node->left != NULL) node = node->left;
	return node;
}

template <typename Comparable>
const Comparable& AVLTree<Comparable>::find_max() const
{
	if( root == NULL )
        throw std::invalid_argument("Invalid argument.");

    AVNode<Comparable> *node = root;

    while(node->right != NULL) 
        node = node->right;
	
    return node->data;
}


// Print the Tree - Pre Order Traversal
template <typename Comparable>
void AVLTree<Comparable>::print(AVNode<Comparable>* node, int depth, std::ostream& out)
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
void AVLTree<Comparable>::print_tree(std::ostream& out)
{
    print(root, 0, out);
    out << endl;    
}

template <typename Comparable>
AVNode<Comparable>* AVLTree<Comparable>::balance(AVNode<Comparable> *temp)
{
    int bal_factor = diff(temp);
	if (bal_factor > 1)
	{
		if (diff(temp->left) > 0)
			temp = ll_rotation(temp);
		else
			temp = lr_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (diff(temp->right) > 0)
			temp = rl_rotation(temp);
		else
			temp = rr_rotation(temp);
	}
	return temp; 
}

/*
* Height of AVL Tree
*/
template <typename Comparable>
int AVLTree<Comparable>::height(AVNode<Comparable>* temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}

/*
* Height Difference
*/
template <typename Comparable>
int AVLTree<Comparable>::diff(AVNode<Comparable>* temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

/*
* Right- Right Rotation
*/
template <typename Comparable>
AVNode<Comparable>* AVLTree<Comparable>::rr_rotation(AVNode<Comparable>* parent)
{
	AVNode<Comparable>* temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}
/*
* Left- Left Rotation
*/
template <typename Comparable>
AVNode<Comparable>* AVLTree<Comparable>::ll_rotation(AVNode<Comparable>* parent)
{
	AVNode<Comparable>* temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

/*
* Left - Right Rotation
*/
template <typename Comparable>
AVNode<Comparable>* AVLTree<Comparable>::lr_rotation(AVNode<Comparable>* parent)
{
	AVNode<Comparable>* temp;
	temp = parent->left;
	parent->left = rr_rotation(temp);
	return ll_rotation(parent);
}

/*
* Right- Left Rotation
*/
template <typename Comparable>
AVNode<Comparable>* AVLTree<Comparable>::rl_rotation(AVNode<Comparable>* parent)
{
	AVNode<Comparable>* temp;
	temp = parent->right;
	parent->right = ll_rotation(temp);
	return rr_rotation(parent);
}

#endif