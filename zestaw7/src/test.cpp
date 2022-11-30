#include "include/test.h"
#include "include/stack.h"
#include "include/rpn.h"
#include <vector>
#include <regex>

Tester::Tester() : testingStack(7) {
    testingStack.push(5);
    testingStack.push(4);
    testingStack.push(3);
    testingStack.push(2);
    testingStack.push(1);
}
void Tester::testCopyConstructor() {
    MyStack<int> tmp(testingStack);
    MyStack<int> test(testingStack);
    tmp.pop();
    tmp.push(15);
    assert(test.equals({1, 2, 3, 4, 5}) && test.size() == 5);
    tmp.clear();
    assert(test.equals({1, 2, 3, 4, 5}) && test.size() == 5);
}
void Tester::testMoveConstructor() {
    MyStack<int> temp(testingStack);
    MyStack<int> test(std::move(temp));
    assert(test.equals({1, 2, 3, 4, 5}) && test.size() == 5 && test.max_size() == 7 && temp.empty());
}
void Tester::testCopyAssignmentOperator() {
    MyStack<int> temp(testingStack);
    MyStack<int> test;
    test = temp;
    temp.clear();
    temp.push(1);
    assert(test.size() == testingStack.size() && test.equals({1,2,3,4,5}) && temp.equals({1}));
}
void Tester::testEmpty() {
    MyStack<int> temp;
    assert(temp.empty());
    temp = testingStack;
    temp.clear();
    assert(temp.empty());
}
void Tester::testFull() {
    MyStack<int> test(testingStack);
    test.push(1);
    test.push(1);
    assert(test.full());
}
void Tester::testSize() {
    assert(testingStack.size() == 5);
}
void Tester::testFront() {
    assert(testingStack.top() == 1);
}
void Tester::testPop() {
    MyStack<int> test(testingStack);
    test.pop();
    assert(test.equals({2,3,4,5}) && test.size() == 4);
}
void Tester::testClear() {
    testingStack.clear();
    assert(testingStack.empty() && testingStack.size() == 0);
}
void Tester::testRpn() {
    std::vector<std::string> input { "-6", "2", "/" };
    ReversePolishNotation rpn(input);
    assert(rpn.result() == -3);
    std::vector<std::string> input2 { "3", "10", "5", "+", "*" };
    rpn.setExpression(input2);
    assert(rpn.result() == 45);
    std::vector<std::string> input3 {"2", "3", "*", "4", "5", "*", "+"};
    rpn.setExpression(input3);
    assert(rpn.result() == 26);
    std::vector<std::string> input4 {"2", "3", "-", "4", "+", "5", "6", "7", "*", "+", "*"};
    rpn.setExpression(input4);
    assert(rpn.result() == 141);

}
void Tester::runTests() {
    std::cout<<"Uruchamianie testów..."<<std::endl;
    testCopyConstructor();
    testMoveConstructor();
    testCopyAssignmentOperator();
    testEmpty();
    testFull();
    testSize();
    testFront();
    testPop();
    testClear();

    testRpn();
    std::cout<<"Testy zakończone pomyślnie!"<<std::endl;
}
