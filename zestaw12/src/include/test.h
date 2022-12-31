#ifndef TEST_H
#define TEST_H
#include "avl_tree.h"
class Test {
private:
    AVLTree<int> testingTree;
    void testInsert();
    void testRemove();
public:
    Test();
    void runTests();
};
#endif
