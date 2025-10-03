#include <stack>
#include <string>
#include <cctype>
#include <iostream>
using namespace std;

int calculate(string s) {
    stack<int> operationsStack;
    int signValue = 1;
    int number = 0;
    int result = 0;

    for (auto &ch : s) {
        if (isdigit(ch)) {
            number = (number * 10) + (ch - '0');
        } 
        else if (ch == '+' || ch == '-') {
            result += number * signValue;
            signValue = (ch == '+') ? 1 : -1;
            number = 0;
        } 
        else if (ch == '(') {
            operationsStack.push(result);
            operationsStack.push(signValue);
            result = 0;
            signValue = 1;
        } 
        else if (ch == ')') {
            result += signValue * number;
            result *= operationsStack.top(); operationsStack.pop();
            result += operationsStack.top(); operationsStack.pop();
            number = 0;
        }
    }
    return result + number * signValue;
}

extern "C" {
    int evalExpression(const char* expr) {
        return calculate(string(expr));
    }
}
