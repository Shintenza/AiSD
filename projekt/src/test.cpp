#include "include/test.h"

void Test::testConstructors() {
    Poly<int> t1;
    assert(t1.size() == 0);
    Poly<int> t2(Term<int>(10, 1));
    assert(t2.size() == 1 && t2.validate({10}, {1}));
    SingleList<Term<int>> list;
    list.push_back(Term<int>(10, 11));
    list.push_back(Term<int>(1, 15));
    list.push_back(Term<int>(3, 4));
    Poly<int> t3(list);
    assert(t3.size() == 3 && t3.validate({1, 10, 3}, {15, 11, 4}));
    Poly<int> t4({1, 2, 3, 4}, {1, 2, 3, 4});
    assert(t4.size() == 4 && t4.validate({4, 3, 2, 1}, {4, 3, 2, 1}));

    Poly<int> t5(t4);
    t4.addTerm(Term<int>(0, 0));
    assert(t5.size() == 4);

    Poly<int> t6(std::move(t5));
    assert(t6.size() == 4 && t5.size() == 0);
}

void Test::testAddition() {
    Poly<int> t1({2, 5, 10}, {2, 1, 0});
    Poly<int> t2({6, 7, 12}, {2, 1, 0});
    Poly<int> r1 = t1 + t2;
    assert(r1.validate({8, 12, 22}, {2, 1, 0}));
    Poly<int> t3({5, -1}, {1, 0});
    Poly<int> r2 = t1 + t3;
    assert(r2.validate({2, 10, 9}, {2, 1, 0}));
    r2 = t3 + t1;
    assert(r2.validate({2, 10, 9}, {2, 1, 0}));
    Poly<int> t4({1, 2, 3, 4}, {10, 9, 8, 7});
    Poly<int> t5({1, 2, 3, 4}, {5, 4, 3, 2});
    Poly<int> r3 = t4 + t5;
    assert(r3.validate({1, 2, 3, 4, 1, 2, 3, 4}, {10, 9, 8, 7, 5, 4, 3, 2}));
    r3 = t5 + t4;
    assert(r3.validate({1, 2, 3, 4, 1, 2, 3, 4}, {10, 9, 8, 7, 5, 4, 3, 2}));
}

void Test::testSubtraction() {
    Poly<int> t1({2, 5, 10}, {2, 1, 0});
    Poly<int> t2({6, 7, 12}, {2, 1, 0});
    Poly<int> r1 = t1 - t2;
    assert(r1.validate({-4, -2, -2}, {2, 1, 0}));
    Poly<int> t3({5, -1}, {1, 0});
    Poly<int> r2 = t1 - t3;
    assert(r2.validate({2, 11}, {2, 0}));
    Poly<int> t4({1, 2, 3, 4}, {10, 9, 8, 7});
    Poly<int> t5({1, 2, 3, 4}, {5, 4, 3, 2});
    Poly<int> r3 = t4 - t5;
    assert(r3.validate({1, 2, 3, 4, -1, -2, -3, -4}, {10, 9, 8, 7, 5, 4, 3, 2}));
    r3 = t5 - t4;
    assert(r3.validate({-1, -2, -3, -4, 1, 2, 3, 4}, {10, 9, 8, 7, 5, 4, 3, 2}));
}

void Test::testMultiplication() {
    Poly<int> t1({1, 2}, {1, 0});
    Poly<int> r1 = t1 * t1;
    assert(r1.validate({1, 4, 4}, {2, 1, 0}));
    Poly<int> t2({2, 10, 9}, {2, 1, 0});
    Poly<int> r2 = t2 * t1;
    assert(r2.validate({2, 14, 29, 18}, {3, 2, 1, 0}));
    r2 = t1 * t2;
    assert(r2.validate({2, 14, 29, 18}, {3, 2, 1, 0}));
    Poly<int> r3 = t1 * t1 * t1;
    assert(r3.validate({1, 6, 12, 8}, {3, 2, 1, 0}));
}

void Test::testValueAt() {
    Poly<int> t1({1, 2, 3}, {1, 2, 3});
    assert(t1.valueAt(1) == 6);
    assert(t1.valueAt(2) == 34);
    assert(t1.valueAt(3) == 102);
    Poly<int> t2({10, 2, 1}, {5, 2, 1});
    assert(t2.valueAt(1) == 13);
    assert(t2.valueAt(2) == 330);
    assert(t2.valueAt(3) == 2451);
}

void Test::testEquals() {
    Poly<int> t1({1, 2, 3}, {3, 2, 1});
    Poly<int> t2({3, 2, 1}, {1, 2, 3});
    Poly<int> t3({3, 2, 1}, {1, 10, 3});
    assert(t1 == t2);
    assert(t1 != t3);
}

void Test::runTests() {
    testConstructors();
    testAddition();
    testSubtraction();
    testMultiplication();
    testValueAt();
}
