#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>

int tests_run = 0;
// ��������������������allow_decimals = false��

void test_generate_operand_integer() {
    Expression exp(10, { "+", "-", "*", "/" }, false, false);
    string operand = exp.generate_operand();
    assert(is_integer(operand));
}

// ��������С����������allow_decimals = true��

void test_generate_operand_decimal() {
    Expression exp(10, { "+", "-", "*", "/" }, false, true);
    string operand = exp.generate_operand();
    assert(is_decimal(operand));
}

//�������ɱ��ʽ�������ţ�allow_parentheses = true��

void test_generate_expression_with_parentheses() {
    Expression exp(10, { "+", "-", "*", "/" }, true, false);
    string expression = exp.generate();
    assert(contains_parentheses(expression));
}

//�������ɱ��ʽ���������ţ�allow_parentheses = false��

void test_generate_expression_without_parentheses() {
    Expression exp(10, { "+", "-", "*", "/" }, false, false);
    string expression = exp.generate();
    assert(!contains_parentheses(expression));
}

//���Ա��ʽ���һ��Ԫ��Ϊ�����ʱ�Ĵ���

void test_expression_ends_with_operator() {
    Expression exp(10, { "+", "-", "*", "/" }, false, false);
    string expression = exp.generate();
    assert(!ends_with_operator(expression));
}

// ���Ա��ʽ���һ��Ԫ�ز��������ʱ�Ĵ���

void test_expression_not_end_with_operator() {
    Expression exp(10, { "+", "-", "*", "/" }, false, false);
    string expression = exp.generate();
    assert(!ends_with_operator(expression));
}

// �������ж���Ĳ����������ܱ�����һ��

void test_generate_all_defined_operators() {
    vector<string> ops = { "+", "-", "*", "/" };
    Expression exp(10, ops, false, false);
    set<string> generated_ops;
    for (int i = 0; i < 100; i++) {
        generated_ops.insert(exp.generate_operator());
    }
    for (const auto& op : ops) {
        assert(generated_ops.find(op) != generated_ops.end());
    }
}

// ����max_numberΪ1ʱ�Ĳ���������

void test_generate_operand_when_max_number_is_one() {
    Expression exp(1, { "+", "-", "*", "/" }, false, false);
    string operand = exp.generate_operand();
    assert(operand == "1");
}

//���Բ���������ֻ����һ��������ʱ�Ĳ���������

void test_generate_operator_when_single_operator() {
    Expression exp(10, { "+" }, false, false);
    string op = exp.generate_operator();
    assert(op == "+");
}

static char* all_tests() {
    mu_run_test(test_generate_operand_integer);
    mu_run_test(test_generate_operand_decimal);
    mu_run_test(test_generate_expression_with_parentheses);
    mu_run_test(test_generate_expression_without_parentheses);
    mu_run_test(test_expression_ends_with_operator);
    mu_run_test(test_generate_all_defined_operators);
    mu_run_test(test_generate_operand_when_max_number_is_one);
    mu_run_test(test_generate_operator_when_single_operator);
    return 0;
}


int main(int argc, char** argv) {
    char* result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
