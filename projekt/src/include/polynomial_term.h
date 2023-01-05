#ifndef TERM_H
#define TERM_H
#include <cassert>

template <typename T>
class Term {
private:
    T coefficient;
    int power;

public:
    Term(const T &c, const int &p);
    ~Term() {}


    T getCoefficient() const { return coefficient; }
    int getPower() const { return power; }
    void setCoefficient(T coefficient) { this->coefficient = coefficient; };
    void setPower(int power);
    bool operator==(const Term& other) const;
    bool operator!=(const Term& other) const;
};

template <typename T>
Term<T>::Term(const T &c, const int &p) : coefficient(c) {
    assert(p >= 0);
    power = p;
}

template <typename T>
void Term<T>::setPower(int power) {
    assert(power >= 0);
    this->power = power;
}

template <typename T>
bool Term<T>::operator==(const Term &other) const {
    if (power == other.power && coefficient == other.coefficient) {
        return true;
    }
    return false;
}

template <typename T>
bool Term<T>::operator!=(const Term &other) const {
    if (!(other==*this)) {
        return true;
    }
    return false;
}
#endif
