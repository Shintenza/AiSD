#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <algorithm> // make_heap, push_heap, pop_heap
#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
class MyPriorityQueue {
    std::vector<T> lst; // działa domyślny konstruktor dla std::vector
    int msize;

  public:
    MyPriorityQueue(int s = 10) : msize(s) { lst.reserve(s); } // default constructor
    ~MyPriorityQueue() { lst.clear(); }
    MyPriorityQueue(const MyPriorityQueue &other);            // copy constructor
    MyPriorityQueue(MyPriorityQueue &&other);                 // move constructor
    MyPriorityQueue &operator=(const MyPriorityQueue &other); // copy assignment operator, return *this
    MyPriorityQueue &operator=(MyPriorityQueue &&other);      // move assignment operator, return *this

    bool empty() const { return lst.empty(); }
    int size() const { return lst.size(); } // liczba elementów w kolejce
    void push(const T &item);
    void push(T &&item);
    T &top() { return lst.front(); } // zwraca element największy, nie usuwa
    void pop();
    void clear() { lst.clear(); } // czyszczenie listy z elementów
    void display();
    bool equals(std::initializer_list<T> other);
    bool equals_raw(std::initializer_list<T> other);
};

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue(const MyPriorityQueue &other) : msize(other.msize) {
    lst = other.lst;
}

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue(MyPriorityQueue &&other) : msize(other.msize) {
    other.msize = 0;
    lst = std::move(other.lst);
}

template <typename T>
MyPriorityQueue<T> &MyPriorityQueue<T>::operator=(const MyPriorityQueue &other) {
    if (this == &other) {
        return *this;
    }
    msize = other.msize;
    lst = other.lst;
    return *this;
}
template <typename T>
MyPriorityQueue<T> &MyPriorityQueue<T>::operator=(MyPriorityQueue &&other) {
    if (this == &other) {
        return *this;
    }
    msize = other.msize;
    lst = std::move(other.lst);

    other.msize = 0;
    return *this;
}
template <typename T>
void MyPriorityQueue<T>::push(const T &item) { // dodanie do kolejki
    assert(lst.size() < msize);
    lst.push_back(item);
    std::push_heap(lst.begin(), lst.end());
}
template <typename T>
void MyPriorityQueue<T>::push(T &&item) { // dodanie do kolejki
    assert(lst.size() < (long unsigned int)msize);
    lst.push_back(std::move(item));
    std::push_heap(lst.begin(), lst.end());
}

template <typename T>
void MyPriorityQueue<T>::pop() { // usuwa element największy
    assert(lst.size() > 0);
    std::pop_heap(lst.begin(), lst.end());
    lst.pop_back();
}

template <typename T>
void MyPriorityQueue<T>::display() {
    int queueSize = size();
    for (int i = 0; i < queueSize; i++) {
        T frontItem = top();
        pop();
        std::cout << frontItem << " " << std::endl;
    }
}

template <typename T>
bool MyPriorityQueue<T>::equals(std::initializer_list<T> other) {
    int queueSize = size();

    if (other.size() != (long unsigned int) queueSize) {
        return false;
    }

    T *orderedQueueItems = new T[queueSize];
    std::vector<T> tmp = lst;
    std::make_heap(tmp.begin(), tmp.end());

    for (int i = 0; i < queueSize; i++) {
        T frontItem = tmp.front();
        orderedQueueItems[i] = frontItem;
        std::pop_heap(tmp.begin(), tmp.end());
        tmp.pop_back();
    }

    int j = 0;
    for (T el : other) {
        if (orderedQueueItems[j] != el) {
            delete[] orderedQueueItems;
            return false;
        }
        j++;
    }

    delete[] orderedQueueItems;
    return true;
}

template <typename T>
bool MyPriorityQueue<T>::equals_raw(std::initializer_list<T> other) {
    if (other.size() != (long unsigned int) lst.size())
        return false;

    int i = 0;
    for (T el : other) {
        if (lst.at(i) != el) {

            return false;
        }
        i++;
    }
    return true;
}
#endif
