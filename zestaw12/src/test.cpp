#include "include/test.h"
#include <ostream>

Test::Test() {
    testingTree.insert(12);
    testingTree.insert(15);
    testingTree.insert(16);
}

void Test::testInsert() {
    assert(testingTree.equals({15, 12, 16}));
    testingTree.insert(17);
    testingTree.insert(18);
    assert(testingTree.equals({15, 12, 17, 16, 18}));
    testingTree.insert(1);
    testingTree.insert(2);
    assert(testingTree.equals({15, 2, 1, 12, 17, 16, 18}));
    testingTree.insert(13);
    testingTree.insert(20);
    assert(testingTree.equals({15, 2, 1, 12, 13, 17, 16, 18, 20}));
}

void Test::testRemove() {
    AVLTree<int> tmp(testingTree);
    tmp.remove(15);
    tmp.display();
}

void Test::runTests() {
    testInsert();
    testRemove();
}
