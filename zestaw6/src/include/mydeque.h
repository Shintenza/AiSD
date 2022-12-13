#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <iostream>
#include <cassert>

template <typename T>
class MyDeque {
    T* tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head; // pierwszy do pobrania
    int tail; // pierwsza wolna pozycja
public:
    MyDeque(int s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor
    ~MyDeque() { delete [] tab; }
    MyDeque(const MyDeque& other); // copy constructor
    MyDeque(MyDeque&& other); // move constructor NIEOBOWIĄZKOWE
    MyDeque& operator=(const MyDeque& other); // copy assignment operator, return *this
    MyDeque& operator=(MyDeque&& other); // move assignment operator, return *this NIEOBOWIĄZKOWE
    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }
    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize-1; }
    void push_front(const T& item); // dodanie na początek O(1)
    void push_front(T&& item); // dodanie na początek O(1) NIEOBOWIĄZKOWE
    void push_back(const T& item); // dodanie na koniec O(1)
    void push_back(T&& item); // dodanie na koniec O(1) NIEOBOWIĄZKOWE
    T& front() { return tab[head]; } // zwraca poczatek
    T& back() { return tab[(tail + msize -1) % msize]; } // zwraca koniec
    void pop_front(); // usuwa początek kolejki O(1)
    void pop_back(); // usuwa koniec kolejki O(1)
    void clear(); // czyszczenie listy z elementow
    void display();
    void debug();
    bool equals(std::initializer_list<T> other);
    // Operacje z indeksami. NIEOBOWIĄZKOWE
    T& operator[](int pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](int pos) const; // dostęp do obiektu const
    void erase(int pos);
    int index(const T& item); // jaki index na liście (-1 gdy nie ma)
    void insert(int pos, const T& item); // inserts item before pos
    void insert(int pos, T&& item); // inserts item before pos
};

template <typename T>
MyDeque<T>::MyDeque(const MyDeque& other) : msize(other.msize), head(other.head), tail(other.tail) {
    tab = new T[msize];
    assert(tab!=nullptr);
    if (other.head == other.tail) return;
    for (int i = head; i != tail; i=(i+1) % msize) {
        tab[i] = other.tab[i];
    }
}
template <typename T>
MyDeque<T>::MyDeque(MyDeque&& other) : msize(other.msize), head(other.head), tail(other.tail) {
    assert(other.tab != nullptr);
    tab = other.tab;

    other.tab = nullptr;
    other.head = 0;
    other.tail = 0;
}
template <typename T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque& other) {
    if (this == &other) return *this;
    delete [] tab;
    tab = new T[other.msize];
    assert(tab!=nullptr);
    head = other.head;
    tail = other.tail;
    msize = other.msize;

    for (int i = head; i != tail; i=(i+1) % msize) {
        tab[i] = other.tab[i];
    }
    return *this;
}
template <typename T>
MyDeque<T>& MyDeque<T>::operator=(MyDeque&& other) {
    if (this == &other) return *this;
    delete [] tab;
    tab = other.tab;
    msize = other.msize;
    head = other.head;
    tail = other.tail;

    other.head = other.tail = 0;
    other.tab = nullptr;
    
    return *this;
}
template <typename T>
void MyDeque<T>::push_front(const T& item) {
    assert(!full());
    head = (head + msize -1) % msize;
    tab[head] = item;
}
template <typename T>
void MyDeque<T>::push_front(T&& item) {
    assert(!full());
    head = (head + msize - 1) % msize;
    tab[head] = std::move(item);
}

template <typename T>
void MyDeque<T>::push_back(const T& item) {
    assert(!full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}
template <typename T>
void MyDeque<T>::push_back(T&& item) {
    assert(!full());
    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}
template <typename T>
void MyDeque<T>::pop_front() {
    assert(this->size() > 0);
    head = (head + 1) % msize;
}
template <typename T>
void MyDeque<T>::pop_back() {
    assert(this->size() > 0);
    tail = (tail + msize - 1) % msize;
}
template <typename T>
void MyDeque<T>::clear() {
    if (this->empty()) return;
    head = tail = 0;
}
template <typename T>
void MyDeque<T>::display() {
    // std::cout<<"Tail: "<<tail<<"; Head: "<<head<<std::endl;
    for (int i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}
template <typename T>
void MyDeque<T>::debug() {
    this->display();
    for (int i = 0; i < msize; i++) {
        std::cout<<tab[i] << " ";
    }
    std::cout << std::endl;
}
template <typename T>
bool MyDeque<T>::equals(std::initializer_list<T> other) {
    if (other.size() != (long unsigned int) this->size())
        return false;
    T* givenArray = new T[other.size()];
    int j = 0;
    for (T el : other) {
        givenArray[i] = el;
        i++;
    }
    for (i = head; i != tail; i=(i+1) % msize) {
        if (givenArray[j] != tab[i])
            return false;
        j++;
    }
    delete [] givenArray;
    return true;
}
template <typename T>
const T& MyDeque<T>::operator[](int pos) const {
    assert(pos < size());
    pos = (head+pos) % msize;
    return tab[pos];
}
template <typename T>
T& MyDeque<T>::operator[](int pos) {
    assert(pos < size());
    pos = (head+pos) % msize;
    return tab[pos];
}
template <typename T>
void MyDeque<T>::erase(int pos) {
    assert(pos < size() && size() > 0);
    if (pos == 0) {
        pop_front();
        return;
    }
    if (pos == size() - 1) {
        pop_back();
        return;
    }

    pos = (head+pos) % msize;
    if (pos > tail) {
        for (int i = pos - 1; i >= tail; i--) {
            tab[i+1] = tab[i];
        }
        head = (head+1) % msize;
    }
    if (pos < tail) {
        for (int i = pos; i < tail; i++) {
            tab[i] = tab[i+1];
        }
        tail = (tail - 1) % msize;
    }
}
template <typename T>
int MyDeque<T>::index(const T& item) {
    int j = 0;
    for (int i = head; i != tail; i=(i+1) % msize) {
        if (tab[i] == item) {
            return j;
        }
        j++;
    }
    return -1;
}
template <typename T>
void MyDeque<T>::insert(int pos, const T& item) {
    assert(!full() && pos <= size());

    if (pos == 0) {
        push_front(item);
        return;
    }
    if (pos == size()){
        push_back(item);
        return;
    }
    pos = (head+pos) % msize;

    if (pos > tail) {
        for (int i = tail; i < pos - 1; i++) {
            tab[i] = tab[i+1];
        }
        head = (head - 1) % msize;
        tab[pos - 1] = item;
    }
    if (pos < tail) {
        for (int i = tail; i >= pos; i--) {
            tab[i+1] = tab[i];
        }
        tail = (tail + 1) % msize;
        tab[pos] = item;
    }

}
template <typename T>
void MyDeque<T>::insert(int pos, T&& item) {
    assert(!full() && pos <= size());

    if (pos == 0) {
        push_front(std::move(item));
        return;
    }
    if (pos == size()){
        push_back(std::move(item));
        return;
    }
    pos = (head+pos) % msize;

    if (pos > tail) {
        for (int i = tail; i < pos - 1; i++) {
            tab[i] = tab[i+1];
        }
        head = (head - 1) % msize;
        tab[pos - 1] = std::move(item);
    }
    if (pos < tail) {
        for (int i = tail; i >= pos; i--) {
            tab[i+1] = tab[i];
        }
        tail = (tail + 1) % msize;
        tab[pos] = std::move(item);
    }
}
#endif
