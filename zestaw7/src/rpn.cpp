#include "include/rpn.h"
#include <regex>

bool ReversePolishNotation::isOperator(std::string &text) {
    if (text.size()!=1)
        return false;
    for (long unsigned int i = 0; i < sizeof(avaliableOperators) / sizeof(std::string); i++) {
        if (text == avaliableOperators[i])
            return true;
    }
    return false;
}
int ReversePolishNotation::calculate(int a, int b, std::string &op) {
    if (op == "+")
        return a+b;
    else if (op == "-") 
        return a-b;
    else if (op == "*") 
        return a*b;
    else 
        return a/b;
}
void ReversePolishNotation::setExpression(std::vector<std::string> &input) {
    rpnExpression = input;
}
int ReversePolishNotation::result() { 
    int result;
    
    for (std::string el : rpnExpression)  {
        if (!isOperator(el)) {
            stack.push(std::stoi(el));
        } else {
            assert(stack.size() >= 2);
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(calculate(b, a, el));
        }
    }
    result = stack.top();
    stack.clear();
    return result;
}
