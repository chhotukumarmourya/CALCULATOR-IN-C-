#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;
class Calculator {
private:
    stack<double> values;
    stack<char> ops;
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
    double applyOperation(double a, double b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/':
                if (b == 0) {
                    cout << "Error: Division by zero\n";
                    return 0;
                }
                return a / b;
        }
        return 0;
    }
    void calculateTop() {
        if (values.size() < 2 || ops.empty()) return;
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperation(a, b, op));
    }
public:
    double evaluate(string expr) {
        for (int i = 0; i < expr.length(); i++) {
            if (expr[i] == ' ') continue;
            if (i > 0 && expr[i] == '(' && isdigit(expr[i-1])) {
                ops.push('*');
            }
            if (i > 0 && isdigit(expr[i]) && expr[i-1] == ')') {
                ops.push('*');
            }
            if (isdigit(expr[i])) {
                double val = 0;
                while (i < expr.length() && isdigit(expr[i])) {
                    val = val * 10 + (expr[i] - '0');
                    i++;
                }
                values.push(val);
                i--;
            }
            else if (expr[i] == '(') {
                ops.push('(');
            }
            else if (expr[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    calculateTop();
                }
                if (!ops.empty()) ops.pop();
            }
            else {
                while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                    calculateTop();
                }
                ops.push(expr[i]);
            }
        }
        while (!ops.empty()) {
            calculateTop();
        }
        return values.empty() ? 0 : values.top();
    }
};
int main() {
    Calculator calc;
    string expression;
    cout << "Enter expression: ";
    getline(cin, expression);
    cout << "Result = " << calc.evaluate(expression);
}