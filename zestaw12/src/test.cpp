#include "include/test.h"
#include <ostream>

void Test::runTests() {
    AVLTree<int> testingTree;
    testingTree.insert(12);
    testingTree.insert(15);
    testingTree.insert(16);
    testingTree.insert(17);
    testingTree.insert(20);

    testingTree.remove(17);
    testingTree.insert(40);
    testingTree.insert(10);
    testingTree.insert(11);
    // testingTree.remove(20);
    // testingTree.remove(10);
    testingTree.remove(15);

    // std::cout<<testingTree.root->left->left->parent-><<std::endl;
    testingTree.display();
}
