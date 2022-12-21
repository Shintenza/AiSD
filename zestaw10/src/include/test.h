#ifndef TEST_H
#define TEST_H
#include "random_binary_tree.h"

class Test {
  private:
    RandomBinaryTree<int> testingTree;
    void testLeafsCounter();
    void testIterLeafsCounter();
    void testTotalCount();
    void testIterTotalCount();
    void testFindMinMax();
    void testIterFindMinMax();
  public:
    Test();
    void runTests();
};
#endif
