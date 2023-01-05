#ifndef POLY_H
#define POLY_H
#include "polynomial_term.h"
#include "singlelist.h"

#include <cassert>
#include <cmath>
#include <iostream>

template <typename T>
class Poly {
private:
    SingleList<Term<T>> termList;
    void addition_subtraction(const Poly &other, Poly &resultPoly, bool addition);

public:
    Poly() : termList(){};
    Poly(Term<T> firstTerm);
    Poly(SingleList<Term<T>> &termList);
    Poly(std::initializer_list<T> coefficients, std::initializer_list<T> powers);
    ~Poly(){};
    Poly(const Poly &other);
    Poly(Poly &&other);

    Poly &operator=(const Poly &other);
    Poly &operator=(Poly &&other);

    Poly operator+(const Poly &other);
    Poly operator-(const Poly &other);
    Poly operator*(const Poly &other);
    bool operator==(const Poly &other) const;
    bool operator!=(const Poly &other) const;

    int size() const { return termList.size(); };

    T valueAt(T x);

    Term<T> front();
    Term<T> back();

    void addTerm(const Term<T> &term);
    void display() const;
    void clear();

    bool validate(std::initializer_list<T> coeff, std::initializer_list<T> pow);
};

template <typename T>
Poly<T>::Poly(Term<T> firstTerm) {
    termList.push_front(firstTerm);
}

template <typename T>
Poly<T>::Poly(SingleList<Term<T>> &lst) {
    int lstSize = lst.size();
    assert(lstSize > 0);
    for (int i = 0; i < lstSize; i++) {
        addTerm(lst.front());
        lst.pop_front();
    }
}

template <typename T>
Poly<T>::Poly(std::initializer_list<T> coefficients, std::initializer_list<T> powers) {
    assert(coefficients.size() == powers.size());
    auto itc = coefficients.begin();
    auto itp = powers.begin();
    while (itc != coefficients.end() || itp != powers.end()) {
        Term<T> term(*itc, *itp);
        addTerm(term);
        ++itc;
        ++itp;
    }
}

template <typename T>
Poly<T>::Poly(const Poly &other) {
    this->termList = other.termList;
}

template <typename T>
Poly<T>::Poly(Poly &&other) {
    this->termList = std::move(other.termList);
}

template <typename T>
Poly<T> &Poly<T>::operator=(const Poly &other) {
    if (this == &other)
        return *this;
    this->termList = other.termList;
    return *this;
}

template <typename T>
Poly<T> &Poly<T>::operator=(Poly &&other) {
    if (this == &other)
        return *this;
    this->termList = std::move(other.termList);
    return *this;
}

template <typename T>
void Poly<T>::addition_subtraction(const Poly &other, Poly &resultPoly, bool addition) {
    SingleNode<Term<T>> *thisNode = termList.getHead();
    SingleNode<Term<T>> *otherNode = other.termList.getHead();

    while (thisNode != nullptr && otherNode != nullptr) {
        Term<T> *thisTerm = thisNode->getNodeValue();
        Term<T> *otherTerm = otherNode->getNodeValue();

        if (thisTerm->getPower() > otherTerm->getPower()) {
            resultPoly.termList.push_back(Term<T>(thisTerm->getCoefficient(), thisTerm->getPower()));
            thisNode = thisNode->getNextNode();
        } else if (thisNode->getNodeValue()->getPower() == otherNode->getNodeValue()->getPower()) {
            if (addition) {
                double value = thisTerm->getCoefficient() + otherTerm->getCoefficient();
                if (value != 0) {
                    resultPoly.termList.push_back(Term<T>(value, thisTerm->getPower()));
                }
            } else {
                double value = thisTerm->getCoefficient() - otherTerm->getCoefficient();
                if (value != 0) {
                    resultPoly.termList.push_back(Term<T>(value, thisTerm->getPower()));
                }
            }
            thisNode = thisNode->getNextNode();
            otherNode = otherNode->getNextNode();
        } else {
            if (addition) {
                resultPoly.termList.push_back(Term<T>(otherTerm->getCoefficient(), otherTerm->getPower()));
            } else {
                resultPoly.termList.push_back(Term<T>(-otherTerm->getCoefficient(), otherTerm->getPower()));
            }
            otherNode = otherNode->getNextNode();
        }
    }

    while (thisNode != nullptr) {
        Term<T> *thisTerm = thisNode->getNodeValue();
        resultPoly.termList.push_back(Term<T>(thisTerm->getCoefficient(), thisTerm->getPower()));
        thisNode = thisNode->getNextNode();
    }

    while (otherNode != nullptr) {
        Term<T> *otherTerm = otherNode->getNodeValue();
        if (addition) {
            resultPoly.termList.push_back(Term<T>(otherTerm->getCoefficient(), otherTerm->getPower()));
        } else {
            resultPoly.termList.push_back(Term<T>(-otherTerm->getCoefficient(), otherTerm->getPower()));
        }
        otherNode = otherNode->getNextNode();
    }
}

template <typename T>
Poly<T> Poly<T>::operator+(const Poly &other) {
    Poly<T> resultPoly;
    addition_subtraction(other, resultPoly, true);
    return resultPoly;
}

template <typename T>
Poly<T> Poly<T>::operator-(const Poly &other) {
    Poly<T> resultPoly;
    addition_subtraction(other, resultPoly, false);
    return resultPoly;
}

template <typename T>
Poly<T> Poly<T>::operator*(const Poly &other) {
    Poly<T> resultPoly;
    SingleNode<Term<T>> *node = termList.getHead();

    while (node != nullptr) {
        Term<T> *term = node->getNodeValue();
        SingleNode<Term<T>> *nodeOther = other.termList.getHead();
        while (nodeOther != nullptr) {
            Term<T> *otherTerm = nodeOther->getNodeValue();
            resultPoly.addTerm(Term<T>(term->getCoefficient() * otherTerm->getCoefficient(), term->getPower() + otherTerm->getPower()));
            nodeOther = nodeOther->getNextNode();
        }
        node = node->getNextNode();
    }
    return resultPoly;
}

template <typename T>
bool Poly<T>::operator==(const Poly &other) const {
    if (other.size() != this->size()) {
        return false;
    }
    SingleNode<Term<T>> *node = termList.getHead();
    SingleNode<Term<T>> *nodeOther = other.termList.getHead();

    while (node != nullptr && nodeOther != nullptr) {
        if (node->getNodeValue() != nodeOther->getNodeValue()) {
            return false;
        }
        node = node->getNextNode();
        nodeOther = nodeOther->getNextNode();
    }

    return true;
}

template <typename T>
bool Poly<T>::operator!=(const Poly &other) const {
    if (!(other == *this))
        return true;
    return false;
}

template <typename T>
T Poly<T>::valueAt(T x) {
    assert(size() > 0);
    int deg = front().getPower();
    T answer = front().getCoefficient();
    SingleNode<Term<T>> *node = termList.getHead();

    for (int i = deg - 1; i >= 0; i--) {
        if (node->getNextNode() != nullptr) {
            Term<T> *term = node->getNextNode()->getNodeValue();
            if (term->getPower() == i) {
                answer = (answer * x) + term->getCoefficient();
                node = node->getNextNode();
            } else {
                answer = answer * x;
            }
        }
    }
    return x * answer;
}

template <typename T>
Term<T> Poly<T>::front() {
    return termList.front();
}

template <typename T>
Term<T> Poly<T>::back() {
    return termList.front();
}

template <typename T>
void Poly<T>::addTerm(const Term<T> &term) {
    if (term.getCoefficient() == 0)
        return;
    termList.add_in_order(term);
}

template <typename T>
void Poly<T>::display() const {
    SingleNode<Term<T>> *node = termList.getHead();
    for (int i = 0; i < termList.size(); i++) {
        Term<T> *term = node->getNodeValue();
        char sign = term->getCoefficient() < 0 ? '-' : '+';
        std::string s = term->getPower() == 0 ? "" : ("*x^" + std::to_string(term->getPower()));

        if (i == 0) {
            std::cout << term->getCoefficient() << s << " ";
        } else if (i == termList.size() - 1) {
            std::cout << sign << " " << std::fabs(term->getCoefficient()) << s;
        } else {
            std::cout << sign << " " << std::fabs(term->getCoefficient()) << s << " ";
        }
        node = node->getNextNode();
    }
    std::cout << std::endl;
}

template <typename T>
void Poly<T>::clear() {
    termList.clear();
}

template <typename T>
bool Poly<T>::validate(std::initializer_list<T> coeff, std::initializer_list<T> pow) {
    assert(coeff.size() == (long unsigned int)pow.size());
    if (coeff.size() != (long unsigned int)size())
        return false;

    auto itc = coeff.begin();
    auto itp = pow.begin();

    SingleNode<Term<T>> *node = termList.getHead();

    while (itc != coeff.end() && itp != pow.end() && node != nullptr) {
        Term<T> *term = node->getNodeValue();
        if (term->getCoefficient() != *itc || term->getPower() != *itp)
            return false;
        node = node->getNextNode();
        ++itc;
        ++itp;
    }
    return true;
}
#endif
