#include "include/test.h"

Tester::Tester() : testingQueue(5) {
    testingQueue.push(1);
    testingQueue.push(2);
    testingQueue.push(3);
    testingQueue.push(4);
    testingQueue.push(5);
}
void Tester::testCopyConstructor() {
    MyQueue<int> temp(testingQueue);
    MyQueue<int> test(temp);
    temp.clear();
    assert(test.full() && test.size() == 5 && test.equals({1, 2, 3, 4, 5}));
}
void Tester::testMoveConstructor() {
    MyQueue<int> temp(testingQueue);
    MyQueue<int> test(std::move(temp));
    assert(temp.empty() && temp.max_size() == 0 && test.full());
    test.pop();
    assert(test.equals({2, 3, 4, 5}));
}
void Tester::testCopyAssignmentOperator() {
    MyQueue<int> temp(testingQueue);
    MyQueue<int> test;
    test = temp;
    temp.clear();
    assert(test.full() && test.equals({1, 2, 3, 4, 5}));
}
void Tester::testMoveAssignmentOperator() {
    MyQueue<int> temp(testingQueue);
    MyQueue<int> test;
    test = std::move(temp);
    assert(temp.empty() && temp.max_size() == 0 && test.full());
}
void Tester::testPush() {
    MyQueue<int> test(3);
    test.push(2);
    test.push(3);
    test.push(4);
    assert(test.size() == 3 && test.equals({2, 3, 4}));
}
void Tester::testPop() {
    MyQueue<int> test(testingQueue);
    test.pop();
    assert(test.size() == 4 && test.equals({2, 3, 4, 5}));
}
void Tester::testClear() {
    MyQueue<int> test(testingQueue);
    test.clear();
    assert(test.empty());
}
void Tester::runTests() {
    std::cout << "Uruchamianie testów..." << std::endl;
    testCopyConstructor();
    testMoveConstructor();
    testCopyAssignmentOperator();
    testMoveAssignmentOperator();
    testPush();
    testPop();
    testClear();
    std::cout << "Testy zakończone pomyślnie!" << std::endl;
}
