#ifndef RPN_H
#define RPN_H
#include <string>
#include <vector>
#include "stack.h"
class ReversePolishNotation {
private:
    std::vector<std::string> rpnExpression;
    const std::string avaliableOperators[4] = { "+", "-", "*", "/" };
    MyStack<int> stack;

    bool isOperator(std::string &text);
    int calculate(int a, int b, std::string &op);
public:
    ReversePolishNotation(std::vector<std::string> &input) : rpnExpression(input) {};
    void setExpression(std::vector<std::string> &input);
    int result();
};
#endif
