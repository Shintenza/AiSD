#include "include/arraylist.h"
#include "include/quicksort.h"
void test () {
    std::cout<<"Uruchomiono testy..."<<std::endl;
    ArrayList<int> test(6);
    // max_size & size
    assert(test.max_size() == 6 && test.size() == 0);
    // push back
    test.push_back(5);
    int testVar = 7;
    test.push_back(testVar);
    assert(test.equals({5, 7}));
    // push front
    test.push_front(12);
    assert(test.equals({12, 5, 7}));
    // reverse
    test.reverse();
    assert(test.equals({7, 5 ,12}));
    // pop back
    test.pop_back();
    assert(test.equals({7, 5}));
    test[2] = 16;
    test[3] = 37;
    // pop front
    test.pop_front();
    assert(test.equals({5, 16, 37}));
    // front && back
    assert(test.back() == 37 && test.front() == 5);
    // insert
    test.insert(1, 15);
    test.insert(3, 14);
    assert(test.equals({5, 15, 16, 14, 37}));
    // sort
    test.sort();
    assert(test.equals({5, 14, 15, 16, 37}));
    // subscript operator
    assert(test[2] == 15);
    // erase
    test.erase(2);
    assert(test.equals({5, 14, 16, 37}));
    // index
    assert(test.index(37) == test.size() - 1);
    assert(test.index(69) == -1);

    // copy constructor
    ArrayList<int> test2(test);
    assert(test2.equals({5, 14, 16, 37}) && test2.size() == 4 && test2.max_size() == 6);
    // move constructor
    ArrayList<int> test3(std::move(test2));
    assert(test3.equals({5, 14, 16, 37}) && test3.size() == 4 && test3.max_size() == 6 && test2.size() == 0);
    test3.push_back(420);
    test3.push_back(1);
    ArrayList<int> test4;
    // copy assignment operator
    test4 = test3;
    assert(test4.equals({5, 14, 16, 37, 420, 1}) && test4.size() == 6 && test4.max_size() == 6);
    //move assignment operator
    test = std::move(test4);
    assert(test.equals({5, 14, 16, 37, 420, 1}) && test.size() == 6 && test.max_size() == 6 && test4.empty());
    test.sort();
    ArrayList<int> test5(4);
    test5[0] = 4; test5[1] = 3; test5[2] = 5; test5[3] = 9;
    test5.sort();
    test.merge(test5);
    assert(test.equals({1, 3, 4, 5, 5, 9, 14, 16, 37, 420}) && test.max_size() == 10 && test.size() == 10);
    std::cout<<"Testy zakończone pomyślnie!"<<std::endl;
}
