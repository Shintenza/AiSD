#ifndef HEAP_H
#define HEAP_H
#include <cassert>
#include <cstring>
#include <iostream>

template <typename T>
class Heap {
  private:
    int msize;
    int last = 0;
    T *tab;
    int getParent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return ((2 * i) + 1); }
    int rightChild(int i) { return ((2 * i) + 2); }
    void shiftUp(int i);
    void shiftDown(int i);

  public:
    Heap(int s = 10);
    ~Heap() { delete[] tab; }
    Heap &operator=(const Heap &other);
    Heap &operator=(Heap &&other);
    void push_back(const T &item);
    void push_back(T &&item);
    void pop();
    bool empty() const { return last == 0; }
    int size() const { return last; }
    void clear();
    T &front() const { return tab[0]; }
    T *getTab() const { return tab; }
};

template <typename T>
Heap<T>::Heap(int s) : msize(s) {
    assert(s > 0);
    tab = new T[s];
    assert(tab != nullptr);
}

template <typename T>
Heap<T> &Heap<T>::operator=(const Heap &other) {
    if (this == &other)
        return *this;
    delete[] tab;
    msize = other.msize;
    last = other.last;
    tab = new T[msize];
    assert(tab != nullptr);
    memcpy(tab, other.tab, msize * sizeof(T));
    return *this;
}

template <typename T>
Heap<T> &Heap<T>::operator=(Heap &&other) {
    if (this == &other)
        return *this;
    msize = other.msize;
    last = other.last;
    tab = other.tab;

    other.msize = 0;
    other.last = 0;
    other.tab = nullptr;
    return *this;
}

template <typename T>
void Heap<T>::shiftUp(int i) {
    while (i > 0 && tab[getParent(i)] < tab[i]) {
        std::swap(tab[getParent(i)], tab[i]);
        i = getParent(i);
    }
}

template <typename T>
void Heap<T>::shiftDown(int i) {
    int maxIndex = i;

    int left = leftChild(i);
    if (left <= last - 1 && tab[left] > tab[maxIndex]) {
        maxIndex = left;
    }

    int right = rightChild(i);
    if (right <= last - 1 && tab[right] > tab[maxIndex]) {
        maxIndex = right;
    }

    if (i != maxIndex) {
        std::swap(tab[i], tab[maxIndex]);
        shiftDown(maxIndex);
    }
}

template <typename T>
void Heap<T>::push_back(const T &item) {
    tab[last] = item;
    last++;
    shiftUp(last - 1);
}

template <typename T>
void Heap<T>::push_back(T &&item) {
    tab[last] = std::move(item);
    last++;
    shiftUp(last - 1);
}

template <typename T>
void Heap<T>::pop() {
    assert(last - 1 >= 0);
    tab[0] = tab[last - 1];
    tab[last - 1] = T();
    last--;
    shiftDown(0);
}

template <typename T>
void Heap<T>::clear() {
    memset(tab, 0, last);
    last = 0;
}
#endif
