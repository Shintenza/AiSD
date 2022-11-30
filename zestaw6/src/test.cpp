#include "include/mydeque.h"
#include "include/test.h"

Tester::Tester() {
    testingDequeue.push_back(3);
    testingDequeue.push_back(2);
    testingDequeue.push_back(1);
    testingDequeue.push_front(4);
}
void Tester::testPushing() {
    MyDeque<int> test(testingDequeue);
    test.push_front(5);
    test.push_back(0);
    assert(test.size() == 6 && test.equals({5, 4, 3, 2, 1, 0}));
}
void Tester::testCopyConstructor() {
    MyDeque<int> tmp(testingDequeue);
    MyDeque<int> test(tmp);
    tmp.clear();
    assert(test.size() == 4 && test.equals({4, 3, 2, 1}));
}
void Tester::testMoveConstructor() {
    MyDeque<int> tmp(testingDequeue);
    MyDeque<int> test(std::move(tmp));
    test.push_front(11);
    assert(test.size() == 5 && test.equals({11, 4, 3, 2, 1}) && tmp.size() == 0 && tmp.empty());
}
void Tester::testCopyAssignmentOperator() {
    MyDeque<int> tmp(testingDequeue);
    MyDeque<int> test;
    test = tmp;
    assert(test.size() == tmp.size() && test.equals({4, 3, 2, 1}));
}
void Tester::testMoveAssignmentOperator() {
    MyDeque<int> tmp(testingDequeue);
    MyDeque<int> test;
    test = std::move(tmp);
    assert(test.size() == 4 && test.equals({4, 3, 2, 1}) && tmp.empty());
}
void Tester::testPopping() {
    MyDeque<int> test(testingDequeue);
    test.pop_back();
    assert(test.equals({4, 3, 2}) && test.size() == 3);
    test.pop_front();
    assert(test.equals({3, 2}) && test.size() == 2);
}
void Tester::testClear() {
    MyDeque<int> test(testingDequeue);
    test.clear();
    assert(test.size() == 0 && test.empty());
}
void Tester::testErase() {
    MyDeque<int> test(testingDequeue);
    // 4 {3} 2 1
    test.erase(1);
    assert(test.size() == 3 && test.equals({4, 2, 1}));
    // 4 2 {1}
    test.erase(2);
    assert(test.size() == 2 && test.equals({4, 2}));
}
void Tester::testSubscriptOperator() {
    MyDeque<int> test(testingDequeue);
    assert(test[0] == 4 && test[3] == 1);
    test[2] = 16;
    assert(test[2] == 16);
}
void Tester::testIndex() {
    MyDeque<int> test(testingDequeue);
    assert(test.index(4) == 0 && test.index(3) == 1 && test.index(1) == 3);
    assert(test.index(22) == -1);
}
void Tester::testInsert() {
    MyDeque<int> test;
    test.push_front(3);
    test.push_front(5);
    test.push_front(6);
    test.push_back(1);
    test.insert(2, 4);
    test.insert(4, 2);
    test.insert(6, 0);
    test.insert(0, 7);
    assert(test.equals({7, 6, 5, 4, 3, 2, 1, 0}) && test.size() == 8);

}
void Tester::runTests() {
    std::cout<<"Uruchamianie testów..." << std::endl;
    testPushing();
    testCopyConstructor();
    testMoveConstructor();
    testCopyAssignmentOperator();
    testMoveAssignmentOperator();
    testPopping();
    testClear();
    testErase();
    testSubscriptOperator();
    testIndex();
    testInsert();
    std::cout<<"Testy zakończone pomyślnie!"<<std::endl;
}
