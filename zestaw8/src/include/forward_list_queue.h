#include <cassert>
#include <forward_list>
#include <iostream>

template <typename T>
class MyQueue {
  private:
    std::forward_list<int> list;
    int msize;
    int length;
  public:
    MyQueue(int s = 10) : msize(s), length(0) {}; // default constructor
    ~MyQueue() { list.clear(); }
    MyQueue(const MyQueue &other);            // copy constructor
    MyQueue(MyQueue &&other);                 // move constructor
    MyQueue &operator=(const MyQueue &other); // copy assignment operator, return *this
    MyQueue &operator=(MyQueue &&other);      // move assignment operator, return *this
    bool empty() const { return list.empty(); }
    bool full() const { return length == msize; }
    int size() const { return length; }
    int max_size() const { return msize; }
    void push(const T &item);           // dodanie na koniec
    void push(T &&item);                // dodanie na koniec
    T &front() { return list.front(); } // zwraca początek
    T &back();                          // zwraca koniec
    void pop();                         // usuwa początek
    void clear();                       // czyszczenie listy z elementów
    void display();
    bool equals(std::initializer_list<T> other);
};
template <typename T>
MyQueue<T>::MyQueue(const MyQueue &other) : msize(other.msize), length(other.length) {
    list = other.list;
}
template <typename T>
MyQueue<T>::MyQueue(MyQueue &&other) : msize(other.msize), length(other.length) {
    list = std::move(other.list);
    other.msize = 0;
    other.length = 0;
}
template <typename T>
MyQueue<T> &MyQueue<T>::operator=(const MyQueue &other) {
    if (this == &other)
        return *this;
    length = other.length;
    msize = other.msize;
    list = other.list;
    return *this;
}
template <typename T>
MyQueue<T> &MyQueue<T>::operator=(MyQueue &&other) {
    if (this == &other)
        return *this;
    list = std::move(other.list);
    msize = other.msize;
    length = other.length;

    other.msize = 0;
    other.length = 0;
    return *this;
}
template <typename T>
void MyQueue<T>::push(const T &item) {
    assert(length < msize);
    if (list.empty()) {
        list.push_front(item);
        length++;
        return;
    }
    auto pos = list.begin();
    while (std::next(pos) != list.end())
        ++pos;
    list.insert_after(pos, item);
    length++;
}
template <typename T>
void MyQueue<T>::push(T &&item) {
    assert(length < msize);
    if (list.empty()) {
        list.push_front(std::move(item));
        length++;
        return;
    }
    auto pos = list.begin();
    while (std::next(pos) != list.end())
        ++pos;
    list.insert_after(pos, std::move(item));
    length++;
}
template <typename T>
T &MyQueue<T>::back() {
    return *list.end();
}
template <typename T>
void MyQueue<T>::pop() {
    assert(length > 0);
    list.pop_front();
    length--;
}
template <typename T>
void MyQueue<T>::clear() {
    if (length == 0)
        return;
    list.clear();
    length = 0;
}
template <typename T>
void MyQueue<T>::display() {
    for (T el : list) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}
template <typename T>
bool MyQueue<T>::equals(std::initializer_list<T> other) {
    if (other.size() != (long unsigned int)this->size())
        return false;
    auto pos = list.begin();
    for (T el : other) {
        if (el != *pos) 
            return false;
        ++pos;
    }
    return true;
}
