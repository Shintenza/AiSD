#ifndef TEST_H
#define TEST_H
#include "bst.h"

class Test {
private:
    BinarySearchTree<int> testingBst;
    void testFindMin();
    void testFindMax();
    void testFindSuccessor();
    void testFindPredecessor();
public:
    Test();
    void runTests();
};
#endif
