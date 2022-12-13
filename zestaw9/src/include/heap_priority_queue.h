#ifndef HEAP_PRIORITY_QUEUE_H
#define HEAP_PRIORITY_QUEUE_H
#include "heap.h"
#include <cassert>
#include <iostream>

template <typename T>
class MyPriorityQueue {
    Heap<T> heap;
    int msize;

  public:
    MyPriorityQueue(int s = 10) : heap(s), msize(s) {} // default constructor
    ~MyPriorityQueue() { heap.clear(); }
    MyPriorityQueue(const MyPriorityQueue &other);            // copy constructor
    MyPriorityQueue(MyPriorityQueue &&other);                 // move constructor
    MyPriorityQueue &operator=(const MyPriorityQueue &other); // copy assignment operator, return *this
    MyPriorityQueue &operator=(MyPriorityQueue &&other);      // move assignment operator, return *this
    bool empty() const { return heap.empty(); }
    int size() const { return heap.size(); } // liczba elementów w kolejce
    void push(const T &item);
    void push(T &&item);
    T &top() { return heap.front(); } // zwraca element największy, nie usuwa
    void pop();
    void clear() { heap.clear(); } // czyszczenie listy z elementów
    void display();
    bool equals(std::initializer_list<T> other);
    bool equals_raw(std::initializer_list<T> other);
};

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue(const MyPriorityQueue &other) : msize(other.msize) {
    heap = other.heap;
}
template <typename T>
MyPriorityQueue<T>::MyPriorityQueue(MyPriorityQueue &&other) : msize(other.msize) {
    other.msize = 0;
    heap = std::move(other.heap);
}

template <typename T>
void MyPriorityQueue<T>::push(const T &item) { // dodanie do kolejki
    assert(heap.size() < msize);
    heap.push_back(item);
}

template <typename T>
void MyPriorityQueue<T>::push(T &&item) { // dodanie do kolejki
    assert(heap.size() < msize);
    heap.push_back(std::move(item));
}

template <typename T>
void MyPriorityQueue<T>::pop() { // usuwa element największy
    assert(heap.size() > 0);
    heap.pop();
}

template <typename T>
void MyPriorityQueue<T>::display() {
    int queueSize = size();
    Heap<T> tmp;
    tmp = heap;
    for (int i = 0; i < queueSize; i++) {
        T frontItem = tmp.front();
        tmp.pop();
        std::cout << frontItem << " " << std::endl;
    }
}
template <typename T>
bool MyPriorityQueue<T>::equals(std::initializer_list<T> other) {
    int queueSize = size();

    if (other.size() != (long unsigned int)queueSize) {
        return false;
    }

    T *orderedQueueItems = new T[queueSize];
    Heap<T> tmp;
    tmp = heap;

    for (int i = 0; i < queueSize; i++) {
        T frontItem = tmp.front();
        orderedQueueItems[i] = frontItem;
        tmp.pop();
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
    if (other.size() != (long unsigned int)heap.size())
        return false;
    T *heapTab = heap.getTab();
    int i = 0;

    for (T el : other) {
        if (heapTab[i] != el) {

            return false;
        }
        i++;
    }
    return true;
}
#endif
