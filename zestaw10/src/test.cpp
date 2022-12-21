#include "include/test.h"

Test::Test() {
    testingTree.insert(1);
    testingTree.insert(2);
    testingTree.insert(3);
    testingTree.insert(4);
    testingTree.insert(5);
    testingTree.insert(6);
    testingTree.insert(7);
    testingTree.insert(8);
    testingTree.insert(9);
    testingTree.insert(10);
    testingTree.insert(11);
    testingTree.insert(12);
}
void Test::testLeafsCounter() {
    assert(testingTree.calc_leafs() == 5);

    RandomBinaryTree<int> test;
    //      1
    //  2       3
    assert(test.calc_leafs() == 0);
    test.insert(1);
    assert(test.calc_leafs() == 1);
    test.insert(2);
    assert(test.calc_leafs() == 1);
    test.insert(3);
    assert(test.calc_leafs() == 2);
}
void Test::testIterLeafsCounter() {
    assert(testingTree.calc_leafs_iter() == 5);

    RandomBinaryTree<int> test;
    //          1
    //      2       4
    //  3
    assert(test.calc_leafs_iter() == 0);
    test.insert(1);
    assert(test.calc_leafs_iter() == 1);
    test.insert(2);
    assert(test.calc_leafs_iter() == 1);
    test.insert(3);
    assert(test.calc_leafs_iter() == 1);
    test.insert(4);
    assert(test.calc_leafs_iter() == 2);
}
void Test::testTotalCount() {
    assert(testingTree.calc_total() == 78);
    RandomBinaryTree<int> test;
    test.insert(30);
    test.insert(11);
    test.insert(19);
    assert(test.calc_total() == 60);
}
void Test::testIterTotalCount() {
    assert(testingTree.iter_calc_total() == 78);
    RandomBinaryTree<int> test;
    test.insert(11);
    test.insert(19);
    test.insert(30);
    assert(test.iter_calc_total() == 60);
}
void Test::testFindMinMax() {
    assert(testingTree.find_min() == 1);
    assert(testingTree.find_max() == 12);
    RandomBinaryTree<int> test;
    test.insert(-2);
    test.insert(20);
    test.insert(-100);
    test.insert(-14);
    assert(test.find_min() == -100);
    assert(test.find_max() == 20);
}
void Test::testIterFindMinMax() {
    assert(testingTree.iter_find_min() == 1);
    assert(testingTree.iter_find_max() == 12);
    RandomBinaryTree<int> test;
    test.insert(-2);
    test.insert(20);
    test.insert(-100);
    test.insert(-14);
    assert(test.iter_find_min() == -100);
    assert(test.iter_find_max() == 20);
}
void Test::runTests() {
    std::cout << "Uruchamianie testów..." << std::endl;
    testLeafsCounter();
    testIterLeafsCounter();
    testTotalCount();
    testIterTotalCount();
    testFindMinMax();
    testIterFindMinMax();
    std::cout << "Testy zakończone pomyślnie..." << std::endl;
}
