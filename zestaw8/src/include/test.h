#include <cassert>
// #include "myqueue.h"
#include "forward_list_queue.h"

class Tester {
private:
    MyQueue<int> testingQueue;
    void testCopyConstructor();
    void testMoveConstructor();
    void testCopyAssignmentOperator();
    void testMoveAssignmentOperator();
    void testPush();
    void testPop();
    void testClear();

public:
    Tester();
    void runTests();
};
