#ifndef TEST_H
#define TEST_H
#include <cassert>
#include "stack.h"

class Tester {
private:
    MyStack<int> testingStack;
    void testCopyConstructor();
    void testMoveConstructor();
    void testCopyAssignmentOperator();
    void testEmpty();
    void testFull();
    void testSize();
    void testFront();
    void testPop();
    void testClear();

    void testRpn();
public:
    Tester();
    void runTests();
};
#endif
