#include <iostream>
#include "binary_search_tree.h"
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <utility>

using namespace std;

int main() {
    // TODO: write tests
    BinarySearchTree<int> tree;
    // insert 5 values into the tree
    tree.insert(6);
    tree.insert(4);
    tree.insert(2);
    tree.insert(8);
    tree.insert(10);
    
    // search the tree
    std::cout << "contains 4? " << std::boolalpha << tree.contains(4) <<
    std::endl;
    int x = 7;
    std::cout << "contains 7? " << std::boolalpha << tree.contains(7) <<
    std::endl;
    // remove the root
    tree.remove(6);
    // find the minimum element
    std::cout << "min: " << tree.find_min() << std::endl;// find the maximum element
    std::cout << "max: " << tree.find_max() << std::endl;
    // print the tree
    std::cout << "tree: " << std::endl;
    tree.print_tree();

    // copy contructor
    cout << "Copy Contructor Test" << endl;
    BinarySearchTree<int> tree1 = tree;
    tree1.insert(20);
    tree1.print_tree();

    // assign operator
    cout << "Assign Operator Test" << endl;
    BinarySearchTree<int> tree2;
    tree2.insert(1);
    tree2.insert(2);
    tree2.print_tree();

    tree2 = tree1;
    tree2.print_tree();



    int A[] = {63, 41, 76, 93, 66, 5, 10, 57, 8, 79, 29, 14, 73, 56, 54, 87, 60,
        22, 23, 90};
    BinarySearchTree<int> tree4;
    for (size_t index = 0; index < 20; index++) {
        tree4.insert(A[index]);
    }
    tree4.print_tree();


}
