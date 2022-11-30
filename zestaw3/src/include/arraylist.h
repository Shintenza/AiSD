// arraylist.h
#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()
#include <cstring>
#include "./quicksort.h"

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template <typename T>
class ArrayList {
    T* tab;
    int msize; // najwieksza mozliwa liczba elementow
    int last; // pierwsza wolna pozycja
public:
    ArrayList(int s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor
    ~ArrayList() { delete [] tab; }
    ArrayList(const ArrayList& other): msize(other.msize), last(other.last) {
        tab = new T[msize];
        assert( tab != nullptr );
        memcpy(tab, other.tab, other.last * sizeof(T));
    }; // copy constructor
    // usage:   ArrayList<int> list2(list1);
    ArrayList(ArrayList&& other) : msize(other.msize), last(other.last) {
        assert(other.tab != nullptr);
        tab = other.tab;

        other.msize = 0;
        other.last = 0;
        other.tab = nullptr ;
    }; // move constructor NIEOBOWIAZKOWE
    // usage:   ArrayList<int> list2(std::move(list1));
    ArrayList& operator=(const ArrayList& other) {
        delete[] tab;
        tab = new T[other.msize];
        assert(tab != nullptr);
        last = other.last;
        msize = other.msize;
        memcpy(tab, other.tab, last * sizeof(T));
        return *this;
    }; // copy assignment operator, return *this
    // usage:   list2 = list1; NIEOBOWIAZKOWE
    ArrayList& operator=(ArrayList&& other) {
        if (this != &other) {
            delete[] tab;
            msize = other.msize;
            last = other.last;
            tab = other.tab;

            other.msize = 0;
            other.last = 0;
            other.tab = nullptr;
        }
        return *this;
    }; // move assignment operator, return *this
    // usage:   list2 = std::move(list1);
    bool empty() const { return last == 0; } // checks if the container has no elements
    bool full() const { return last == msize; } // checks if the container is full
    int size() const { return last; } // liczba elementow na liscie
    int max_size() const { return msize; } // najwieksza mozliwa liczba elementow
    void push_front(const T& item) {
        pushFrontMethod(item);
    }; // dodanie na poczatek
    void push_front(T&& item) {
        pushFrontMethod(item);
    }  // dodanie na poczatek NIEOBOWIAZKOWE
    void push_back(const T& item) {
        pushBackMethod(item);
    } // dodanie na koniec
    void push_back(T&& item) {
        pushBackMethod(item);
    }; // dodanie na koniec NIEOBOWIAZKOWE
    T& front() {
        if (last == 0) {
            std::cout<<"The list is empty"<<std::endl;
            exit(1);
        }
        return tab[0];
    } // zwraca poczatek, nie usuwa, error dla pustej listy
    T& back() {
        if (last == 0) {
            std::cout<<"The list is empty"<<std::endl;
            exit(1);
        }
        return tab[last - 1];
    } // zwraca koniec, nie usuwa, error dla pustej listy
    void pop_front() {
        if (last == 0) {
            std::cout<<"The list is empty"<<std::endl;
            exit(1);
        }
        for (int i = 1; i <= last; i++)   {
            tab[i-1] = tab[i];
        }
        tab[last] = 0;
        last--;
    }; // usuwa poczatek, error dla pustej listy
    void pop_back() {
        if (last==0) {
            std::cout<<"The list is empty"<<std::endl;
            return;
        }
        tab[last] = 0;
        last--;
    }; // usuwa koniec, error dla pustej listy
    void clear() {
        memset(tab, 0, last);
        last = 0;
    }; // czyszczenie listy z elementow
    void display() {
        for (int i = 0; i < last; i++) {
            std::cout<<tab[i]<< (i == last - 1 ? "" : " ");
        }
        std::cout<<std::endl;
    }; // lepiej zdefiniowac operator<<
    void reverse() {
        int j = last - 1;
        for (int i = 0; i <= j; i ++) {
            if (i>=j)
                break;
            std::swap(tab[i], tab[j]);
            j--;
        }
    }; // odwracanie kolejnosci
    void sort() {
        quickSort(tab, 0, last - 1);
    }; // sortowanie listy
    void merge(ArrayList& other) {
        T* tempArr = new T[other.size() + this->size()];
        int i = 0, j=0, k=0;
        while (i < last && j < other.size()) {
            if (this->tab[i] <= other.tab[j]) {
                tempArr[k] = this->tab[i];
                i++;
            } else {
                tempArr[k] = other.tab[j];
                j++;
            }
            k++;
        }
        while (i < this->size()) {
            tempArr[k] = this->tab[i];
            i++;
            k++;
        }
        while(j < other.size()) {
            tempArr[k] = other.tab[j];
            j++;
            k++;
        }
        delete[] tab;
        tab = tempArr;
        msize = other.size() + this->size();
        last = msize;
    }; //  merges two sorted lists into one
    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator
    T& operator[](int pos) {
        if (pos >= msize) {
            std::cout<<"Given index is invalid"<<std::endl;
            exit(1);
        }
        if (pos + 1 > last) {
            last = pos + 1;
        }
        return tab[pos];
    }; // podstawienie L[pos]=item
    const T& operator[](int pos) const {
        if (pos >= msize) {
            std::cout<<"invalid index"<<std::endl;
            exit(1);
        }
        return tab[pos];
    }; // odczyt L[pos]
    void erase(int pos) {
        if (pos>= msize) {
            std::cout<<"Given index is invalid"<<std::endl;
            exit(1);
        }
        if (pos >= last && pos <= msize - 1)
            return;
        if (pos == 0)
            this->pop_front();
        else if (pos == last - 1) 
            this->pop_back();
        else {
            for (int i = pos; i < last; i++) {
                tab[i] = tab[i+1];
            }
            last--;
        }
    }; // usuniecie elementu na pozycji pos
    int index(const T& item) {
        for (int i = 0; i < last; i++) {
            if (item == tab[i])
                return i;
        }
        return -1;
    }; // jaki index na liscie (-1 gdy nie ma)
    void insert(int pos, const T& item) {
        insertMethod(pos, item);
    }; // inserts item before pos
    void insert(int pos, T&& item) {
        insertMethod(pos, item);
    }; // inserts item before pos
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << (i == L.last - 1 ? "" : " ");   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
    bool equals(std::initializer_list<T> other) {
        if (other.size()!=(long unsigned int)last) {
            return false;
        }
        int i = 0;
        for (T el : other) {
            if (el != tab[i]) {
                return false;
            }
            i++;
        }
        return true;
    }
private:
    void pushFrontMethod(T item) {
        if (last == msize) {
            std::cout<<"missing space"<<std::endl;
            exit(1);
        }
        for (int i = last-1; i >= 0; i--) {
            tab[i+1] = tab[i];
        }
        last++;
        tab[0] = item;
    }
    void pushBackMethod(T item) {
        if (last == msize) {
            std::cout<<"missing space"<<std::endl;
            exit(1);
        }
        tab[last] = item;
        last++;
    }
    void insertMethod(int pos, T item) {
        if (last == msize) {
            std::cout<<"The list is full"<<std::endl;
            exit(1);
        }
        if (pos >= msize) {
            std::cout<<"Given index is invalid"<<std::endl;
            exit(1);
        }
        if (pos == last) 
            this->push_back(item);
        else if(pos == 0)
            this->push_front(item);
        else {
            for (int i = last - 1; i >= pos; i--) {
                tab[i+1] = tab[i];
            }
            tab[pos]=item;
            last++;
        }
    }
};

#endif
