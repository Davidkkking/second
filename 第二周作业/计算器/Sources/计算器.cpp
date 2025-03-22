#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

// ��������ȼ��ж�
int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0; // �������ȼ����
}

// ���ʽ��ֵ���ĺ���
double calculate(string expr) {
    stack<char> ops;   // �����ջ
    stack<double> nums; // ������ջ
    string num;        // ��ʱ�洢��λ����

    auto compute = [&]() { // ���㹤�ߺ���
        double b = nums.top(); nums.pop();
        double a = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();
        switch (op) {
        case '+': nums.push(a + b); break;
        case '-': nums.push(a - b); break;
        case '*': nums.push(a * b); break;
        case '/':
            if (b == 0) throw runtime_error("�������");
            nums.push(a / b); break;
        }
        };

    for (int i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (isdigit(c) || c == '.') {  // ���ִ���
            num += c;
            if (i == expr.size() - 1 || !isdigit(expr[i + 1]) && expr[i + 1] != '.') {
                nums.push(stod(num));
                num.clear();
            }
        }
        else if (c == '(') {         // ��������ջ
            ops.push(c);
        }
        else if (c == ')') {         // �����Ŵ���
            while (ops.top() != '(') compute();
            ops.pop(); // ����������
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') { // ���������
            // ����ǰ�ø��ţ����ʽ��ͷ��ǰ�������ţ�
            if (c == '-' && (i == 0 || expr[i - 1] == '(')) {
                nums.push(0); // ���㴦����(Сϸ��)
            }
            // �Ƚ����ȼ�������
            while (!ops.empty() && priority(ops.top()) >= priority(c)) {
                compute();
            }
            ops.push(c);
        }
    }

    // ����ʣ�������
    while (!ops.empty()) compute();

    return nums.top();
}

int main() {
    string expr;
    cout << "������ʽ��";
    cin >> expr;
    double result = calculate(expr);
    cout << "��������" << result << endl;
    return 0;
}