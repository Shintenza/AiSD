#ifndef SINGLELIST_H
#define SINGLELIST_H

#include "polynomial_term.h"
#include <cassert>  // assert()
#include <iostream> // deklaracje strumieni cout, cin, cerr

template <typename T> class SingleList;

template <typename T> class SingleNode {
private:
    T value;
    SingleNode *next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T &item, SingleNode *ptr = nullptr)
        : value(item), next(ptr) {}
    ~SingleNode() {} // destruktor
    friend class SingleList<T>;

public:
    T *getNodeValue() { return &value; };
    SingleNode<T> *getNextNode() const { return next; };
};

template <typename T> class SingleList {
    SingleNode<T> *head, *tail;
    int length;

public:
    SingleList() : head(nullptr), tail(nullptr), length(0) {}
    ~SingleList();                       // tu trzeba wyczyscic wezly
    SingleList(const SingleList &other); // copy constructor
    // usage:   SingleList<int> list2(list1);
    SingleList(SingleList &&other); // move constructor NIEOBOWIAZKOWE
    // usage:   SingleList<int> list2(std::move(list1));
    SingleList &operator=(
        const SingleList &other); // copy assignment operator, return *this
    // usage:   list2 = list1;
    SingleList &
    operator=(SingleList &&other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE
    bool empty() const { return head == nullptr; }
    int size() const { return length; } // O(n) bo trzeba policzyc
    void push_front(const T &item);     // O(1), L.push_front(item)
    void
    push_front(T &&item); // O(1), L.push_front(std::move(item)) NIEOBOWIAZKOWE
    void push_back(const T &item); // O(1), L.push_back(item)
    void
    push_back(T &&item); // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE
    void add_in_order(const T &term); // exclusive for polynomials
    T &front() const;                 // zwraca poczatek, nie usuwa
    T &back() const;                  // zwraca koniec, nie usuwa
    void pop_front();                 // usuwa poczatek O(1)
    void pop_back();                  // usuwa koniec O(n)
    void clear();                     // czyszczenie listy z elementow O(n)
    void display();                   // O(n)
    void reverse();                   // O(n)
    // Operacje z indeksami. NIEOBOWIAZKOWE
    T &operator[](int pos);             // podstawienie L[pos]=item
    const T &operator[](int pos) const; // odczyt L[pos]
    void erase(int pos);
    int index(const T &item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T &item); // inserts item before pos,
    void insert(int pos, T &&item);      // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
    bool equals(std::initializer_list<T> other);
    SingleNode<T> *getHead() const { return head; }
};

template <typename T> SingleList<T>::~SingleList() {
    // I sposob.
    for (SingleNode<T> *node; !empty();) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    // II sposob.
    // while (!empty()) { pop_front(); }
}
template <typename T>
SingleList<T>::SingleList(const SingleList<T> &other) : length(other.length) {
    if (other.length == 0) {
        tail = head = nullptr;
    }
    tail = head = new SingleNode<T>(other.head->value);
    head->next = tail;
    if (other.length > 1) {
        SingleNode<T> *nextOtherNode = other.head->next;
        while (nextOtherNode != nullptr) {
            tail->next = new SingleNode<T>(nextOtherNode->value);
            tail = tail->next;
            nextOtherNode = nextOtherNode->next;
        }
    }
}
template <typename T>
SingleList<T>::SingleList(SingleList &&other) : length(other.length) {
    if (other.length == 0)
        tail = head = nullptr;
    assert(other.head != nullptr && other.tail != nullptr);

    head = other.head;
    tail = other.head;
    SingleNode<T> *node = other.head;

    while (node != nullptr) {
        node = other.head->next;
        other.head = nullptr;
        other.head = node;
    }

    other.length = 0;
}
template <typename T>
SingleList<T> &SingleList<T>::operator=(const SingleList<T> &other) {
    if (this == &other)
        return *this;
    SingleNode<T> *node = this->head;

    while (node != nullptr) {
        node = head->next;
        delete head;
        head = node;
    }

    if (other.length == 0) {
        head = tail = nullptr;
        length = 0;
    }
    tail = head = new SingleNode<T>(other.head->value);
    head->next = tail;

    if (other.length > 1) {
        node = other.head->next;
        while (node != nullptr) {
            tail->next = new SingleNode<T>(node->value);
            tail = tail->next;
            node = node->next;
        }
    }
    length = other.length;
    return *this;
}
template <typename T>
SingleList<T> &SingleList<T>::operator=(SingleList &&other) {
    if (this == &other)
        return *this;

    if (other.length == 0) {
        head = tail = nullptr;
        length = 0;
        return *this;
    }
    assert(other.head != nullptr && other.tail != nullptr);
    head = other.head;
    tail = other.tail;

    SingleNode<T> *node = other.head;
    while (node != nullptr) {
        node = other.head->next;
        other.head = nullptr;
        other.head = node;
    }
    length = other.length;
    other.length = 0;
    return *this;
}
template <typename T> void SingleList<T>::push_front(const T &item) {
    if (!empty()) {
        head = new SingleNode<T>(item, head);
    } else {
        head = tail = new SingleNode<T>(item);
    }
    length++;
}
template <typename T> void SingleList<T>::push_front(T &&item) {
    if (!empty()) {
        head = new SingleNode<T>(std::move(item), head);
    } else {
        head = tail = new SingleNode<T>(std::move(item));
    }
    length++;
}

template <typename T> void SingleList<T>::push_back(const T &item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(item);
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(item);
    }
    length++;
}
template <typename T> void SingleList<T>::add_in_order(const T &term) {
    if (empty()) {
        head = tail = new SingleNode<T>(term);
        length++;
        return;
    }

    int givenTermPower = term.getPower();
    SingleNode<T> *node = head;
    SingleNode<T> *tmp = node->next;

    if (size() == 1 && givenTermPower == node->value.getPower()) {
        node->getNodeValue()->setCoefficient(
            term.getCoefficient() + node->getNodeValue()->getCoefficient());
        return;
    }
    if ((size() == 1 && givenTermPower > node->value.getPower()) ||
        givenTermPower > node->value.getPower()) {
        push_front(term);
        return;
    }
    if (size() == 1 && givenTermPower < node->value.getPower()) {
        push_back(term);
        return;
    }

    while (node->next != nullptr &&
           givenTermPower < node->next->value.getPower()) {
        node = node->next;
    }

    if (node->next == nullptr &&
        node->getNodeValue()->getPower() != givenTermPower) {
        push_back(term);
        return;
    }

    if (node->next->getNodeValue()->getPower() == givenTermPower) {
        node->next->value.setCoefficient(
            node->next->getNodeValue()->getCoefficient() +
            term.getCoefficient());
    } else {
        tmp = node->next;
        node->next = new SingleNode<T>(term);
        node->next->next = tmp;
        length++;
    }
}
template <typename T> void SingleList<T>::push_back(T &&item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(std::move(item));
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(std::move(item));
    }
    length++;
}
template <typename T> T &SingleList<T>::front() const {
    assert(length != 0 && head != nullptr);
    return head->value;
}
template <typename T> T &SingleList<T>::back() const {
    assert(length != 0 && tail != nullptr);
    return tail->value;
}
template <typename T> void SingleList<T>::display() {
    SingleNode<T> *node = head;
    while (node != nullptr) {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T> void SingleList<T>::pop_front() {
    assert(!empty());
    SingleNode<T> *node = head; // zapamietujemy
    if (head == tail) {         // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        head = head->next;
    }
    delete node;
    length--;
}

template <typename T> void SingleList<T>::pop_back() {
    assert(!empty());
    SingleNode<T> *node = tail; // zapamietujemy
    if (head == tail) {         // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        // Szukamy poprzednika ogona.
        SingleNode<T> *before = head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;
    length--;
}
template <typename T> void SingleList<T>::clear() {
    if (length == 0)
        return;
    SingleNode<T> *node = head;
    while (node != nullptr) {
        node = head->next;
        delete head;
        head = node;
    }
    head = tail = nullptr;
    length = 0;
}
template <typename T> void SingleList<T>::reverse() {
    if (length <= 1)
        return;
    SingleNode<T> *before = nullptr;
    SingleNode<T> *after = head;
    SingleNode<T> *tmpNode;

    while (after != nullptr) {
        tmpNode = after->next;
        after->next = before;
        before = after;
        after = tmpNode;
    }
    std::swap(head, tail);
}
template <typename T> T &SingleList<T>::operator[](int pos) {
    assert(pos < size());
    int i = 0;
    SingleNode<T> *node = head;
    while (i != pos && node != nullptr) {
        node = node->next;
        i++;
    }
    return node->value;
}
template <typename T> const T &SingleList<T>::operator[](int pos) const {
    assert(pos < length);
    int i = 0;
    SingleNode<T> *node = head;
    while (i != pos && node != nullptr) {
        node = node->next;
        i++;
    }
    return node->value;
}
template <typename T> void SingleList<T>::erase(int pos) {
    assert(pos >= 0 && pos < length);
    if (pos == 0) {
        pop_front();
        return;
    }
    if (pos == length - 1) {
        pop_back();
        return;
    }
    int i = 0;
    SingleNode<T> *node = head;
    SingleNode<T> *tmp;
    while (i != pos - 1 && node != nullptr) {
        node = node->next;
        i++;
    }
    tmp = node->next;
    node->next = node->next->next;
    delete tmp;
    length--;
}
template <typename T> int SingleList<T>::index(const T &item) {
    int i = 0;
    SingleNode<T> *node = head;
    while (node != nullptr) {
        if (node->value == item)
            return i;
        i++;
        node = node->next;
    }
    return -1;
}
template <typename T> void SingleList<T>::insert(int pos, const T &item) {
    assert(pos <= length);
    if (pos == 0) {
        push_front(item);
        return;
    }
    if (pos == length) {
        push_back(item);
        return;
    }
    int i = 0;
    SingleNode<T> *node = head;
    SingleNode<T> *tmp;

    while (i < pos - 1 && node != nullptr) {
        node = node->next;
        i++;
    }
    tmp = node->next;
    node->next = new SingleNode<T>(item, tmp);
    length++;
}
template <typename T> void SingleList<T>::insert(int pos, T &&item) {
    assert(pos <= length);
    if (pos == 0) {
        push_front(item);
        return;
    }
    if (pos == length) {
        push_back(item);
        return;
    }
    int i = 0;
    SingleNode<T> *node = head;
    SingleNode<T> *tmp;
    while (i < pos - 1 && node != nullptr) {
        node = node->next;
        i++;
    }
    tmp = node->next;
    node->next = new SingleNode<T>(std::move(item), tmp);
    length++;
}
template <typename T>
bool SingleList<T>::equals(std::initializer_list<T> other) {
    if (other.size() != (long unsigned int)this->length)
        return false;
    SingleNode<T> *node = this->head;
    for (T el : other) {
        if (el != node->value) {
            return false;
        }
        node = node->next;
    }
    return true;
}
#endif
