//Ruth Massock
//Assignment 4
//COP 4530

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "stack.h"

using namespace std;
using namespace cop4530;

// Returns the precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Checks if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Checks if a character is an operand
bool isOperand(char c) {
    return isalnum(c) || c == '.';
}

// Converts an infix expression to a postfix expression
string infixToPostfix(const string& infix) {
    stringstream output;
    Stack<char> operators;
    bool lastWasOperator = true;

    for (char token : infix) {
        if (isspace(token)) continue;

        if (isOperand(token)) {
            if (!lastWasOperator) throw runtime_error("Invalid infix expression");
            output << token;
            lastWasOperator = false;
        } else if (token == '(') {
            operators.push(token);
            lastWasOperator = true;
        } else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output << ' ' << operators.top();
                operators.pop();
            }
            if (operators.empty()) throw runtime_error("Mismatched parentheses");
            operators.pop();
            lastWasOperator = false;
        } else if (isOperator(token)) {
            if (lastWasOperator) throw runtime_error("Invalid infix expression");
            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                output << ' ' << operators.top();
                operators.pop();
            }
            operators.push(token);
            output << ' ';
            lastWasOperator = true;
        } else {
            throw runtime_error("Invalid token in infix expression");
        }
    }

    while (!operators.empty()) {
        if (operators.top() == '(') throw runtime_error("Mismatched parentheses");
        output << ' ' << operators.top();
        operators.pop();
    }

    return output.str();
}

// Evaluates a postfix expression
int evaluatePostfix(const string& exp) {
    Stack<int> st;
    stringstream ss(exp);
    string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            st.push(stoi(token));
        } else if (isOperator(token[0])) {
            if (st.size() < 2) {
                throw runtime_error("Error - Too few operands");
            }
            int val1 = st.top(); st.pop();
            int val2 = st.top(); st.pop();

            switch (token[0]) {
                case '+': st.push(val2 + val1); break;
                case '-': st.push(val2 - val1); break;
                case '*': st.push(val2 * val1); break;
                case '/': st.push(val2 / val1); break;
            }
        } else {
            throw runtime_error("Invalid token in postfix expression");
        }
    }

    if (st.size() != 1) {
        throw runtime_error("Error - Too few operands");
    }

    return st.top();
}

int main() {
    string line;

    while (true) {
        cout << "Enter an infix expression (or 'q' to quit): ";
        getline(cin, line);
        if (line == "q") break;

        try {
            string postfix = infixToPostfix(line);
            cout << "The InFix Notation is: " << line << endl;
            cout << "The PostFix Notation is: " << postfix << endl;

            int result = evaluatePostfix(postfix);
            cout << "Results are: " << result << endl;
        } catch (const runtime_error& e) {
            cout << "Results are: " << e.what() << endl;
        }
    }

    return 0;
}
