#ifndef TEST_H
#define TEST_H
#include "polynomial.h"

class Test {
private:
    void testConstructors();
    void testAddition();
    void testSubtraction();
    void testMultiplication();
    void testValueAt();
    void testEquals();
public:
    void runTests();
};
#endif
