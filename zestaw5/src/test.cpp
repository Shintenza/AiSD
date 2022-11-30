#include <iostream>
#include <cassert>
#include "include/doublelist.h"

void test() {
    DoubleList<int> list;
    // push back && front
    list.push_back(2);
    list.push_front(1);
    list.push_back(3);
    assert(list.size() == 3 && list.equals({1, 2, 3}));
    // copy constructor
    DoubleList<int> list2(list);
    assert(list2.size() == 3 && list.equals({1, 2, 3}));
    // copy assignment operator
    list2.push_back(4);
    list2.push_back(5);
    DoubleList<int> list3;
    list3 = list2;
    assert(list3.size() == 5 && list3.equals({1, 2, 3, 4, 5}));
    // move assignment operator
    list = std::move(list3);
    assert(list3.size() == 0 && list.size() == 5 && list.equals({1, 2, 3, 4, 5}));
    // pop front
    list.pop_front();
    assert(list.size() == 4 && list.equals({2, 3, 4, 5}));
    // pop back
    list.pop_back();
    assert(list.size() == 3 && list.equals({2, 3, 4}));
    // clear
    list.clear();
    assert(list.size() == 0);
    // subscript operator overloading
    list.push_back(1);
    list.push_back(2);
    list.push_back(7);
    list.push_back(4);
    list[2] = 3;
    assert(list.size() == 4 && list.equals({1, 2, 3, 4}));
    // erase 
    list.erase(0);
    assert(list.size() == 3 && list.equals({2, 3, 4}));
    list.erase(2);
    assert(list.size() == 2 && list.equals({2, 3}));
    list.push_front(1);
    list.push_back(4);
    list.erase(2);
    assert(list.size() == 3 && list.equals({1, 2, 4}));
    list.erase(1);
    assert(list.size() == 2 && list.equals({1, 4}));
    // index
    list.push_back(5);
    list.push_back(6);
    list.push_back(8);
    assert(list.index(2137) == -1 && list.index(1) == 0 && list.index(5) == list.size() - 3);
    // insert
    list.insert(1, 2);
    list.insert(2, 3);
    list.insert(6, 7);
    list.insert(9, 10);
    list.insert(12, 13);
    assert(list.size() == 13 && list.equals({1, 2, 3, 4, 5, 6, 7, 8, 0, 10, 0, 0, 13}));
}
