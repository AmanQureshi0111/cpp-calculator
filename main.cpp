#include <bits/stdc++.h>
#include "crow_all.h"
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
        else if (ch == '(') { // start again
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

int main() {
    // string expression;
    // cout << "**************** Rules To Write Expression ******************************" << endl;
    // cout << "1. Expression can contain digits, '+', '-', '(', ')', and spaces.\n"
    //      << "2. Expression must be valid.\n"
    //      << "3. '+' cannot be used as a unary operator (i.e., '+1' and '+(2 + 3)' are invalid).\n"
    //      << "4. '-' can be used as a unary operator (i.e., '-1' and '-(2 + 3)' are valid).\n"
    //      << "5. No two consecutive operators are allowed.\n";
    // cout << "**************************************************************************" << endl;

    // cout << "Enter Expression: ";
    // getline(cin, expression);

    // int ans = calculate(expression);
    // cout << "Result: " << ans << endl;

    // return 0;
    crow::SimpleApp app;
     cout << "**************** Rules To Write Expression ******************************" << endl;
    cout << "1. Expression can contain digits, '+', '-', '(', ')', and spaces.\n"
         << "2. Expression must be valid.\n"
         << "3. '+' cannot be used as a unary operator (i.e., '+1' and '+(2 + 3)' are invalid).\n"
         << "4. '-' can be used as a unary operator (i.e., '-1' and '-(2 + 3)' are valid).\n"
         << "5. No two consecutive operators are allowed.\n";
    cout << "**************************************************************************" << endl;
    CROW_ROUTE(app, "/calc/<string>")
    ([](string expr){
        int ans = calculate(expr);
        return crow::response(to_string(ans));
    });

    app.port(8080).multithreaded().run();
}
