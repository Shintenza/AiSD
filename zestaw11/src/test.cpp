#include "include/test.h"

Test::Test() {
    testingBst.insert(10);
    testingBst.insert(12);
    testingBst.insert(7);
    testingBst.insert(11);
    testingBst.insert(5);
    testingBst.insert(8);
    testingBst.insert(4);
    testingBst.insert(1);
    testingBst.insert(3);
}
void Test::testFindMin() {
    assert(*testingBst.find_min() == 1);
}
void Test::testFindMax() {
    assert(*testingBst.find_max() == 12);
}
void Test::testFindSuccessor() {
    assert(*testingBst.find_successor(1) == 3);
    assert(*testingBst.find_successor(8) == 10);
    assert(*testingBst.find_successor(11) == 12);
    assert(testingBst.find_successor(12) == nullptr);
}
void Test::testFindPredecessor() {
    assert(*testingBst.find_predecessor(12) == 11);
    assert(*testingBst.find_predecessor(4) == 3);
    assert(*testingBst.find_predecessor(10) == 8);
    assert(*testingBst.find_predecessor(7) == 5);
    assert(testingBst.find_predecessor(1) == nullptr);
}
void Test::runTests() {
    std::cout<<"Uruchamianie testów..."<<std::endl;
    testFindMin();
    testFindMax();
    testFindSuccessor();
    testFindPredecessor();
    std::cout<<"Testy zakończone pomyślnie!"<<std::endl;
}
