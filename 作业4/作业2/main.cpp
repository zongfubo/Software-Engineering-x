#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <windows.h> // ���� Windows API

using namespace std;

class Expression {
private:
    int max_number;
    vector<string> operators;
    bool allow_parentheses;
    bool allow_decimals;

public:
    Expression(int max_number, vector<string> operators, bool allow_parentheses, bool allow_decimals)
        : max_number(max_number), operators(operators), allow_parentheses(allow_parentheses), allow_decimals(allow_decimals) {}

    string generate_operand() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, max_number);

        if (allow_decimals) {
            double operand = dist(gen) + (double)rand() / RAND_MAX;
            char buffer[50];
            sprintf(buffer, "%.2f", operand);
            return string(buffer);
        }
        else {
            return to_string(dist(gen));
        }
    }

    string generate_operator() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, operators.size() - 1);
        return operators[dist(gen)];
    }

    string generate() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(2, 5);
        int num_operands = dist(gen);
        vector<string> expr;
        bool need_operator = false;

        for (int i = 0; i < num_operands; ++i) {
            if (need_operator) {
                expr.push_back(generate_operator());
            }

            if (allow_parentheses && i > 0 && i < num_operands - 1 && (rand() % 2)) {
                expr.push_back("(");
                expr.push_back(generate_operand());
                expr.push_back(generate_operator());
                expr.push_back(generate_operand());
                expr.push_back(")");
                need_operator = true;
            }
            else {
                expr.push_back(generate_operand());
                need_operator = true;
            }
        }

        if (find(operators.begin(), operators.end(), expr.back()) != operators.end()) {
            expr.pop_back();
        }

        string result;
        for (const auto& e : expr) {
            result += e + " ";
        }
        return result;
    }
};

void print_to_file(const vector<string>& questions) {
    ofstream file("questions.txt");
    for (const auto& question : questions) {
        file << question << endl;
    }
    file.close();
    cout << "��Ŀ��������ļ� questions.txt" << endl;
}

void print_to_console(const vector<string>& questions) {
    cout << "���ɵ���Ŀ��" << endl;
    for (const auto& question : questions) {
        cout << question << endl;
    }
}

int main() {
    // ���ÿ���̨�������Ϊ UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // ���ÿ���̨�����ܹ���ʾ UTF-8
    SetConsoleCP(CP_UTF8);

    srand(time(0));
    int numQuestions, maxNumber;
    bool withParentheses, withDecimals;
    vector<string> operators;

    while (true) {
        cout << "������Ŀ������";
        cin >> numQuestions;
        cout << "���������ֵ��";
        cin >> maxNumber;
        cout << "�Ƿ�������ţ�(0/1)��";
        cin >> withParentheses;
        cout << "�Ƿ����С����(0/1)��";
        cin >> withDecimals;
        cout << "��������� (+ - * /)���ÿո�ָ���";
        string op;
        operators.clear();
        while (cin >> op) {
            operators.push_back(op);
            if (cin.peek() == '\n') break;
        }

        Expression exp(maxNumber, operators, withParentheses, withDecimals);
        vector<string> questions;
        for (int i = 0; i < numQuestions; ++i) {
            questions.push_back(exp.generate() + " =");
        }

        int outputChoice;
        cout << "ѡ�������ʽ��1������̨��2���ļ�����";
        cin >> outputChoice;
        if (outputChoice == 1) {
            print_to_console(questions);
        }
        else if (outputChoice == 2) {
            print_to_file(questions);
        }
        else {
            cout << "��Ч��ѡ��" << endl;
        }

        char continueGenerating;
        cout << "�Ƿ����������Ŀ��(Y/N): ";
        cin >> continueGenerating;
        if (continueGenerating == 'N' || continueGenerating == 'n') {
            break;
        }
    }

    return 0;
}