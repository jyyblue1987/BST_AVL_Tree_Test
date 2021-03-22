#include <iostream>
#include "avl_tree.h"
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <utility>

using namespace std;

int main() {
    AVLTree<int> tree;
    // insert 5 values into the tree
    tree.insert(6);
    tree.insert(4);
    tree.insert(2);
    tree.insert(8);
    tree.insert(10);
    // search the tree
    std::cout << "contains 4? " << std::boolalpha << tree.contains(4) <<
    std::endl;
    std::cout << "contains 7? " << std::boolalpha << tree.contains(7) <<
    std::endl;
    // remove the root
    tree.remove(4);
    // find the minimum element
    std::cout << "min: " << tree.find_min() << std::endl;
    // find the maximum element
    std::cout << "max: " << tree.find_max() << std::endl;
    // print the tree
    std::cout << "tree: " << std::endl;
    tree.print_tree();
}
