#include <iostream>
#include <assert.h>
#include "include/singlelist.h"

void test () {
    SingleList<int> list; 
    int testValue = 4;
    std::cout<<"Uruchamianie testów..."<<std::endl;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(testValue);
    // size && push_back
    assert(list.size() == 4 && list.equals({1, 2, 3, 4}));
    // copy constructor
    SingleList<int> list2(list);
    assert(list2.size() == 4 && list.equals({1, 2, 3, 4}));
    // move constructor
    SingleList<int> list3(std::move(list2));
    assert(list2.size() == 0 && list3.equals({1, 2, 3, 4}));
    // copy assignment operator
    list.push_back(5);
    list.push_back(6);
    list3 = list;
    assert(list3.size() == 6 && list3.equals({1, 2, 3, 4, 5, 6}));
    // move assignment operator && push front
    list3.push_back(7);
    list3.push_front(0);
    list = std::move(list3);
    assert(list.size() == 8 && list.equals({0, 1, 2, 3, 4, 5, 6, 7}));
    // front && back
    assert(list.front() == 0 && list.back() == 7);
    // reverse
    list.reverse();
    assert(list.size() == 8 && list.equals({7, 6, 5, 4, 3, 2, 1, 0}) && list.front() == 7 && list.back() == 0);
    // reading list value using index
    assert(list[2] == 5 && list[4] == 3 && list[7] == 0);
    // changing values using subscript operator
    list[3] = 12;
    list[7] = 15;
    list[0] = 17;
    list[4] = 20;
    assert(list[3] == 12 && list.back() == 15 && list.front() == 17 && list[4] == 20 && list.size() == 8);
    // clear
    list.clear();
    assert(list.size() == 0);
    // subscript operator when pos is bigger than max length
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list[8] = 99;
    assert(list.equals({1, 2, 3, 0, 0, 0, 0, 0, 99}) && list.size() == 9);
    // erase
    list[3] = 4;
    list[4] = 5;
    list[5] = 6;
    list.erase(0);
    list.erase(7);
    list.erase(2);
    assert(list.size() == 6 && list.front() == 2 && list.back() == 0 && list.equals({2, 3, 5, 6, 0, 0}));
    // index
    assert(list.index(6) == 3 && list.index(69) == -1);
    // insert
    list.insert(2, 4);
    list.insert(0, 1);
    list.insert(8, 99);
    assert(list.size() == 9 && list.equals({1, 2, 3, 4, 5, 6, 0, 0, 99}));
    std::cout<<"Testy zakończone pomyślnie!"<<std::endl;
}
