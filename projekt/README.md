# Projekt zaliczeniowy - implementacja wielomianów na bazie listy powiązanej pojedynczo

## Kompilacja i uruchamianie
Aby skompilować i uruchomić projekt należy skorzystać z polecenia `make run`. Projekt nie wymaga żadnych dodatkowych zależności (nie wliczając w to podstawowych
narządzi takich jak *make* lub kompilator).

## Struktura projektu
```
├── Makefile
├── README.md
└── src
    ├── include
    │   ├── polynomial.h        // szablon wielomianu
    │   ├── polynomial_term.h   // szablon pojedynczego wyrazu wielomianu
    │   ├── singlelist.h        // zmodyfikowana wersja listy pojedynczo wiązanej z lekcji 4
    │   └── test.h              // plik nagłówkowy z definicją klasy testowej
    ├── main.cpp               
    └── test.cpp                // plik źródłowy z implementacją testów

```
## Zmiany w liście pojedynczo wiązanej
- dodanie metody `add_in_order` odpowiedzialnej za umieszczanie wyrazów w liście w odpowiedniej kolejności
- dodanie metody `getHead` zwracającej wskaźnik do head listy
- zmiana struktury SingleNode na klasę, prywatny dostęp do pól: `value`, `next`, konstruktorów; dodanie geterów do `value` i `next`; ustawienie `friend 
class SingleList` (wszystkie działania miały na celu bezpośredni dostęp do węzłów listy z poziomu wielomianu bez możliwości modyfikacji ich)

## polynomial_term.h
```
template <typename T>
class Term {
private:
    T coefficient;
    int power;

public:
    Term(const T &c, const int &p); // konstruktor z waliadacją poprawności wprowadzonej potęgi
    ~Term() {}


    T getCoefficient() const { return coefficient; }
    int getPower() const { return power; }
    void setCoefficient(T coefficient) { this->coefficient = coefficient; };    // zmiana współczynnika wielomianu (przydatne w podstawowych operacjach)
    void setPower(int power);   // zmiana potęgi (przydatne przy mnożeniu)
    bool operator==(const Term& other) const;   // porównywanie dwóch węzłów
    bool operator!=(const Term& other) const;
}
```
## polynomial.h
```

template <typename T>
class Poly {
private:
    SingleList<Term<T>> termList;
    void addition_subtraction(const Poly &other, Poly &resultPoly, bool addition);

public:
    Poly() : termList(){};          // tworzenie pustego wielomianu
    Poly(Term<T> firstTerm);        // konstruktor z podaniem pierwszego elementu
    Poly(SingleList<Term<T>> &termList);    // utworzenie wielomianu na podstawie listy elementów
    Poly(std::initializer_list<T> coefficients, std::initializer_list<T> powers);   // manualne stworzenie wielomianu: {1, 2, 3}, {2, 1, 0} oznacza x^2 + 2x + 3
    ~Poly() { clear(); };       // destruktor
    Poly(const Poly &other);    // konstruktor kopiujący
    Poly(Poly &&other);         // move konstruktor

    Poly &operator=(const Poly &other); // copy assignment operator
    Poly &operator=(Poly &&other);      // move assignment operator

    Poly operator+(const Poly &other);  // dodawanie
    Poly operator-(const Poly &other);  // odejmowanie
    Poly operator*(const Poly &other);  // mnożenie
    bool operator==(const Poly &other) const;   // porównywanie
    bool operator!=(const Poly &other) const;   // porównywanie

    int size() const { return termList.size(); };   // ilość elementów wielomianu

    T valueAt(T x);     // obliczanie wartości z użyciem algorytmu Hornera

    Term<T> front();    // zwracanie pierwszego elementu
    Term<T> back();     // zwracanie ostatniego elementu

    void addTerm(const Term<T> &term);      // dodawanie elementu w odpowiedniej kolejności
    void display() const;       // wyświetlanie
    void clear();       // czyszczenie listy z elementami wielomiany

    bool validate(std::initializer_list<T> coeff, std::initializer_list<T> pow);        // funkcja do testów
};
```
