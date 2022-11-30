#ifndef MY_QUEUE
#define MY_QUEUE
#include <cstring>
#include <iostream>

template <typename T>
class MyQueue {
    T *tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head;  // pierwszy do pobrania
    int tail;  // pierwsza wolna pozycja
  public:
    MyQueue(int s = 10) : msize(s + 1), head(0), tail(0) {
        tab = new T[s + 1];
        assert(tab != nullptr);
    } // default constructor
    ~MyQueue() { delete[] tab; }
    MyQueue(const MyQueue &other);            // copy constructor
    MyQueue(MyQueue &&other);                 // move constructor
    MyQueue &operator=(const MyQueue &other); // copy assignment operator, return *this
    MyQueue &operator=(MyQueue &&other);      // move assignment operator, return *this
    bool empty() const { return head == tail; }
    bool full() const { return (head + msize - 1) % msize == tail; }
    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize - 1; }
    void push(const T &item);                             // dodanie na koniec
    void push(T &&item);                                  // dodanie na koniec
    T &front() { return tab[head]; }                      // zwraca początek
    T &back() { return tab[(tail + msize - 1) % msize]; } // zwraca koniec
    void pop();                                           // usuwa początek
    void clear();                                         // czyszczenie listy z elementów
    void display();
    bool equals(std::initializer_list<T> other);
};

template <typename T>
MyQueue<T>::MyQueue(const MyQueue &other)
    : msize(other.msize), head(other.head), tail(other.tail) {
    tab = new T[msize];
    assert(tab != nullptr);
    memcpy(tab, other.tab, other.msize * sizeof(T));
}
template <typename T>
MyQueue<T>::MyQueue(MyQueue &&other)
    : msize(other.msize), head(other.head), tail(other.tail) {
    assert(other.tab != nullptr);
    tab = other.tab;
    other.msize = 1;
    other.head = 0;
    other.tail = 0;
    other.tab = nullptr;
}
template <typename T>
MyQueue<T> &MyQueue<T>::operator=(const MyQueue &other) {
    if (this == &other)
        return *this;
    delete[] tab;
    tab = new T[other.msize];
    assert(tab != nullptr);
    head = other.head;
    tail = other.tail;
    msize = other.msize;
    memcpy(tab, other.tab, msize * sizeof(T));
    return *this;
}
template <typename T>
MyQueue<T> &MyQueue<T>::operator=(MyQueue &&other) {
    if (this == &other)
        return *this;
    assert(other.tab != nullptr);

    delete[] tab;

    tab = other.tab;
    head = other.head;
    tail = other.tail;
    msize = other.msize;

    other.head = 0;
    other.tail = 0;
    other.msize = 1;
    other.tab = nullptr;
    return *this;
}
template <typename T>
void MyQueue<T>::push(const T &item) {
    assert(!this->full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}
template <typename T>
void MyQueue<T>::push(T &&item) {
    assert(!this->full());
    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}
template <typename T>
void MyQueue<T>::pop() {
    assert(!this->empty());
    tab[head] = T();
    head = (head + 1) % msize;
}
template <typename T>
void MyQueue<T>::clear() {
    head = tail = 0;
    for (int i = head; i != tail; i = (i + 1) % msize) {
        tab[i] = T();
    }
}
template <typename T>
void MyQueue<T>::display() {
    for (int i = head; i != tail; i = (i + 1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
};
template <typename T>
bool MyQueue<T>::equals(std::initializer_list<T> other) {
    if (other.size() != (long unsigned int)this->size())
        return false;

    int j = 0;
    T *givenArray = new T[other.size()];
    for (T el : other) {
        givenArray[j] = el;
        j++;
    }
    j = 0;
    for (int i = head; i != tail; i = (i + 1) % msize) {
        if (tab[i] != givenArray[j])
            return false;
        j++;
    }
    return true;
}
#endif
