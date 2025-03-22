#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

// 运算符优先级判断
int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0; // 括号优先级最低
}

// 表达式求值核心函数
double calculate(string expr) {
    stack<char> ops;   // 运算符栈
    stack<double> nums; // 操作数栈
    string num;        // 临时存储多位数字

    auto compute = [&]() { // 运算工具函数
        double b = nums.top(); nums.pop();
        double a = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();
        switch (op) {
        case '+': nums.push(a + b); break;
        case '-': nums.push(a - b); break;
        case '*': nums.push(a * b); break;
        case '/':
            if (b == 0) throw runtime_error("除零错误");
            nums.push(a / b); break;
        }
        };

    for (int i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (isdigit(c) || c == '.') {  // 数字处理
            num += c;
            if (i == expr.size() - 1 || !isdigit(expr[i + 1]) && expr[i + 1] != '.') {
                nums.push(stod(num));
                num.clear();
            }
        }
        else if (c == '(') {         // 左括号入栈
            ops.push(c);
        }
        else if (c == ')') {         // 右括号处理
            while (ops.top() != '(') compute();
            ops.pop(); // 弹出左括号
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') { // 运算符处理
            // 处理前置负号（表达式开头或前有左括号）
            if (c == '-' && (i == 0 || expr[i - 1] == '(')) {
                nums.push(0); // 补零处理负号(小细节)
            }
            // 比较优先级并计算
            while (!ops.empty() && priority(ops.top()) >= priority(c)) {
                compute();
            }
            ops.push(c);
        }
    }

    // 处理剩余运算符
    while (!ops.empty()) compute();

    return nums.top();
}

int main() {
    string expr;
    cout << "输入表达式：";
    cin >> expr;
    double result = calculate(expr);
    cout << "计算结果：" << result << endl;
    return 0;
}