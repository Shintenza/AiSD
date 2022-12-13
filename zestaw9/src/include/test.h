#ifndef TEST_H
#define TEST_H
// #include "my_priority_queue.h"
#include "heap_priority_queue.h"

class Test {
    MyPriorityQueue<int> testingPriorityQueue;
    void testCopyConstructor();
    void testMoveConstructor();
    void testTop();
    void testPush();
    void testPop();

  public:
    Test();
    void runTests();
};
#endif
