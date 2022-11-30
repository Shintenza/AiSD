// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
    int length;
public:
    DoubleList() : head(nullptr), tail(nullptr), length(0) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList& other); // copy constructor
    // usage:   DoubleList<int> list2(list1);

    DoubleList(DoubleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));

    DoubleList& operator=(const DoubleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    int size() const { return length; } 
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1)
    void push_back(T&& item); // O(1) NIEOBOWIAZKOWE
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(n)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](int pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](int pos) const; // dostep do obiektu const
    void erase(int pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T& item); // inserts item before pos,
    void insert(int pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.

    bool equals(std::initializer_list<T> other);
};

template <typename T>
DoubleList<T>::~DoubleList() {
    DoubleNode<T> *node = head;
    while (node != nullptr) {
        node = node->next;
        delete head;
        head = node;
    }
}
template <typename T>
DoubleList<T>::DoubleList(const DoubleList& other) : length(other.length) {
    if (other.length == 0) {
        head = tail = nullptr;
    }
    head = tail = new DoubleNode<T>(other.head->value);
    if (length > 1) {
        DoubleNode<T> *node = other.head->next;
        while (node != nullptr) {
            tail->next = new DoubleNode<T>(node->value, nullptr, tail);
            tail = tail->next;
            node = node->next;
        }
        
    }
}
template <typename T>
DoubleList<T>::DoubleList(DoubleList&& other) : length(other.length) {
    if (other.length == 0) {
        tail = head = nullptr;
    }
    assert(other.head != nullptr && other.tail != nullptr);
    head = other.head;
    tail = other.tail;
    // DoubleNode<T> *node = other.head;
    // while (node != nullptr) {
    //     node = other.head->next;
    //     other.head = nullptr;
    //     other.head = node;
    // }
    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
}
template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& other) {
    if (this == &other) return *this;
    DoubleNode<T> *node = this->head;
    while (node != nullptr) {
        node = head->next;
        delete head;
        head = node;
    }
    length = other.length;
    if (length == 0) {
        head = tail = nullptr;
    }

    head = tail = new DoubleNode<T>(other.head->value);
    if (length > 1) {
        DoubleNode<T> *node = other.head->next;
        while (node != nullptr) {
            tail->next = new DoubleNode<T>(node->value, nullptr, tail);
            tail = tail->next;
            node = node->next;
        }
    }
    return *this;
}
template <typename T>
DoubleList<T>& DoubleList<T>::operator=(DoubleList&& other) {
    if (this == &other) return *this;
    length = other.length;
    if (length == 0) {
        head = tail = nullptr;
        return *this;
    }
    assert(other.head != nullptr && other.tail != nullptr);
    head = other.head;
    tail = other.tail;
    // DoubleNode<T> *node = other.head;
    // while (node != nullptr) {
    //     node = other.head->next;
    //     other.head = nullptr;
    //     other.head = node;
    // }
    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
    return *this;
}

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
    length++;
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
    length++;
}
template <typename T>
void DoubleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new DoubleNode<T>(item, nullptr, tail);
        tail = tail->next;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
    length++;
}
template <typename T>
void DoubleList<T>::push_back(T&& item) {
    if (!empty()) {
        tail->next = new DoubleNode<T>(std::move(item), nullptr, tail);
        tail = tail->next;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
    length++;
}
template <typename T>
void DoubleList<T>::pop_front(){
    assert(!empty());
    DoubleNode<T> *node = head;

    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete node;
    length--;
}
template <typename T>
void DoubleList<T>::pop_back() {
    assert(!empty());
    DoubleNode<T> *node = tail;

    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail->prev->next = nullptr;
        tail = tail->prev;
    }
    delete node;
    length--;
}
template <typename T>
void DoubleList<T>::clear() {
    if (length == 0)
        return;
    DoubleNode<T> *node = head;
    while(node != nullptr) {
        node = node->next;
        delete head;
        head = node;
    }
    head = tail = nullptr;
    length = 0;
}
template <typename T>
void DoubleList<T>::display() {
    DoubleNode<T> *node = head;
    while (node != nullptr) {
        std::cout<<node->value<<" ";
        node = node->next;
    }
    std::cout << std::endl;

}
template <typename T>
void DoubleList<T>::display_reversed() {
    DoubleNode<T> *node = tail;
    while (node != nullptr) {
        std::cout<<node->value<<" ";
        node = node->prev;
    }
    std::cout << std::endl;
}
template <typename T>
T& DoubleList<T>::operator[](int pos) {
    assert(pos < length && length > 0);
    if (pos == 0)
        return this->front();
    if (pos == length - 1)
        return this->back();
    if (pos > length - 1 - pos) {
        int j = length - 1;
        DoubleNode<T> *node = tail;
        while (j != pos && node != nullptr) {
            node = node->prev;
            j--;
        }
        return node->value;
    } else {
        int j = 0;
        DoubleNode<T> *node = head;
        while (j != pos && node != nullptr) {
            node = node->next;
            j++;
        }
        return node->value;
    }
}
template <typename T>
const T& DoubleList<T>::operator[](int pos) const {
    assert(pos<length && length > 0);
    if (pos == 0)
        return this->front();
    if (pos == length - 1)
        return this->back();
    if (pos > length - 1 - pos) {
        int j = length - 1;
        DoubleNode<T> *node = tail;
        while (j != pos && node != nullptr) {
            node = node->prev;
            j--;
        }
        return node->value;
    } else {
        int j = 0;
        DoubleNode<T> *node = head;
        while (j != pos && node != nullptr) {
            node = node->next;
            j++;
        }
        return node->value;
    }
    
}
template <typename T>
void DoubleList<T>::erase(int pos) {
    assert(pos < length && length > 0);
    if (pos == 0) {
        pop_front();
        return;
    }
    if (pos == length - 1) {
        pop_back();
        return;
    }
    if (pos > length - 1 - pos) {
        int j = length - 1;
        DoubleNode<T> *node = tail;
        while (j != pos && node != nullptr) {
            node = node->prev;
            j--;
        }
        // std::cout<<node->value<<std::endl;
        // node->prev = node->prev->prev;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    } else {
        int j = 0;
        DoubleNode<T> *node = head;
        while (j != pos && node != nullptr) {
            node = node->next;
            j++;
        }
        node->next->prev = node->prev;
        node->prev->next = node->next;
        delete node;
    }
    length--;
}
template <typename T>
int DoubleList<T>::index(const T& item) {
    int i = 0; 
    DoubleNode<T> *node = head;
    while (node!=nullptr) {
        if (node->value == item) 
            return i;
        i++;
        node = node->next;
    }
    return -1;
}
template <typename T>
void DoubleList<T>::insert(int pos, const T& item) {
    if (pos == 0) {
        push_front(item);
        return;
    } 
    if (pos == length) {
        push_back(item);
        return;
    }
    if (pos > length) {
        int i = 0;
        while (i < pos - length + 1) {
            tail->next = new DoubleNode<T>(T(), nullptr, tail);
            tail = tail->next;
            i++;
        }
        length = pos + 1;
        tail->value = item;
        return;
    }
    DoubleNode<T> *node;
    DoubleNode<T> *tmp;
    if (pos > length - 1 - pos) {
        node = tail;
        int j = length - 1;
        while (j != pos && node != nullptr) {
            node = node->prev;
            j--;
        }

    } else {
        node = head;
        int j = 0;
        while (j != pos && node != nullptr) {
            node = node->next;
            j++;
        }
    }
    tmp = node->prev;
    node->prev = new DoubleNode<T>(item, node, tmp);
    tmp->next = node->prev;
    length++;
}
template <typename T>
void DoubleList<T>::insert(int pos, T&& item) {
    if (pos == 0) {
        push_front(std::move(item));
        return;
    } 
    if (pos == length) {
        push_back(std::move(item));
        return;
    }
    if (pos > length) {
        int i = 0;
        while (i < pos - length + 1) {
            tail->next = new DoubleNode<T>(T(), nullptr, tail);
            tail = tail->next;
            i++;
        }
        length = pos + 1;
        tail->value = std::move(item);
        return;
    }
    DoubleNode<T> *node;
    DoubleNode<T> *tmp;
    if (pos > length - 1 - pos) {
        node = tail;
        int j = length - 1;
        while (j != pos && node != nullptr) {
            node = node->prev;
            j--;
        }

    } else {
        node = head;
        int j = 0;
        while (j != pos && node != nullptr) {
            node = node->next;
            j++;
        }
    }
    tmp = node->prev;
    node->prev = new DoubleNode<T>(std::move(item), node, tmp);
    tmp->next = node->prev;
    length++;
}
template <typename T>
bool DoubleList<T>::equals(std::initializer_list<T> other) {
    if (other.size() != (long unsigned int) this->length) 
        return false;
    DoubleNode<T> *node = this->head;
    for (T el : other) {
        if (el != node->value) 
            return false;
        node = node->next;
    }
    return true;
}
#endif

// EOF
