#include "include/test.h"
#include "include/heap.h"

Test::Test() : testingPriorityQueue(6) {
    testingPriorityQueue.push(30);
    testingPriorityQueue.push(9);
    testingPriorityQueue.push(1);
    testingPriorityQueue.push(20);
    testingPriorityQueue.push(17);
}

void Test::testCopyConstructor() {
    MyPriorityQueue<int> tmp(testingPriorityQueue);
    MyPriorityQueue<int> test(tmp);
    tmp.pop();
    assert(test.size() == 5 && test.equals({30, 20, 17, 9, 1}));
    tmp.clear();
    assert(test.size() == 5 && test.equals({30, 20, 17, 9, 1}));
}

void Test::testMoveConstructor() {
    MyPriorityQueue<int> tmp(testingPriorityQueue);
    MyPriorityQueue<int> test(std::move(tmp));
    assert(tmp.size() == 0 && tmp.empty());
    assert(test.size() == 5 && test.equals({30, 20, 17, 9, 1}));
}

void Test::testTop() {
    MyPriorityQueue<int> test(testingPriorityQueue);
    test.pop();
    assert(test.top() == 20);
}

void Test::testPush() {
    assert(testingPriorityQueue.size() == 5);
    assert(testingPriorityQueue.equals({30, 20, 17, 9, 1}));
    assert(testingPriorityQueue.equals_raw({30, 20, 1, 9, 17}));
}

void Test::testPop() {
    MyPriorityQueue<int> test(testingPriorityQueue);
    test.pop();
    test.pop();
    test.pop();
    assert(test.size() == 2 && test.equals({9, 1}));
}

void Test::runTests() {
    std::cout << "Uruchamianie testów..." << std::endl;
    testCopyConstructor();
    testMoveConstructor();
    testTop();
    testPush();
    testPop();
    std::cout << "Testy zakończone pomyślnie!" << std::endl;
}
