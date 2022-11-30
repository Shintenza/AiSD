#ifndef STACK_H
#define STACK_H
#include <iostream>
#include "./singlelist.h"

template <typename T>
class MyStack {
private:
    SingleList<T> lst;
    int msize;
public:
    MyStack(int s=10) : msize(s) {}; // default constructor
    ~MyStack() { lst.clear(); };
    MyStack(const MyStack& other); // copy constructor
    MyStack(MyStack&& other); // move constructor
    MyStack& operator=(const MyStack& other); // copy assignment operator, return *this
    MyStack& operator=(MyStack&& other); // move assignment operator, return *this
    bool empty() const { return lst.empty(); } // checks if the container has no elements
    bool full() const { return lst.size() == msize; }
    int size() const { return lst.size(); }
    int max_size() const { return msize; }
    void push(const T& item);
    void push(T&& item);
    T& top() { return lst.front(); } // zwraca koniec, nie usuwa
    void pop() { lst.pop_front(); } // usuwa koniec
    void clear() { lst.clear(); }
    void display();
    bool equals(std::initializer_list<T> other);
};

template <typename T>
MyStack<T>::MyStack(const MyStack& other) : msize(other.msize) {
    if (other.size() == 0)
        return;
    lst = other.lst;
}

template <typename T>
MyStack<T>::MyStack(MyStack&& other) : msize(other.msize) {
    other.msize = 0;
    lst = std::move(other.lst);
}

template <typename T>
MyStack<T>& MyStack<T>::operator=(const MyStack& other) {
    if (this == &other) return *this;
    msize = other.msize;
    lst = other.lst;
    return *this;
}

template <typename T>
MyStack<T>& MyStack<T>::operator=(MyStack&& other) {
    if (this == &other) return *this;
    msize = other.msize();
    lst = std::move(other.lst);
    other.msize = 0;
}
template <typename T>
void MyStack<T>::push(const T& item) {
    assert(lst.size() < msize);
    lst.push_front(item); 
}
template <typename T>
void MyStack<T>::push(T&& item) {
    assert(lst.size() < msize);
    lst.push_front(std::move(item)); 
}

template <typename T>
void MyStack<T>::display() {
    if (lst.size() == 0) return;
    for (int i = 0; i < lst.size(); i++) {
        std::cout << lst[i] << " ";
    }
    std::cout<<std::endl;
}

template <typename T>
bool MyStack<T>::equals(std::initializer_list<T> other) {
    if (other.size() != (long unsigned int) this->size())
        return false;
    int i = 0;
    for (T item : other) {
        if (item != lst[i]) 
            return false;
        i++;
    }
    return true;
}

#endif
