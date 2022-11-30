#ifndef TEST_H
#define TEST_H
void test();
#include "./mydeque.h"
class Tester {
private:
    MyDeque<int> testingDequeue;  

    void testPushing();
    void testCopyConstructor();
    void testMoveConstructor();
    void testCopyAssignmentOperator();
    void testMoveAssignmentOperator();
    void testPopping();
    void testClear();
    void testErase();
    void testSubscriptOperator();
    void testIndex();
    void testInsert();
public:
    Tester();
    void runTests();
};
#endif
