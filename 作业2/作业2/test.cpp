#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>

int tests_run = 8;

int maxSum(int a[], int size);

// ²âÊÔÓÃÀı1
static const char* test_case1() {
    int a[] = { 1, -2, 3 };
    int result = maxSum(a, 3);
    mu_assert("error, maxSum(a, 3) != 3",result == 3);
    return 0;
}
// ²âÊÔÓÃÀı2
static const char* test_case2() {
    int a[] = { 1, 2, 3 };
    int result = maxSum(a, 3);
    mu_assert("error, maxSum(a, 3) != 6", result == 6);
    return 0;
}
// ²âÊÔÓÃÀı3
static const char* test_case3() {
    int a[] = { -1, 4, -2, 3 };
    int result = maxSum(a, 4);
    mu_assert("error, maxSum(a, 4) != 5", result == 5);
    return 0;
}
// ²âÊÔÓÃÀı4
static const char* test_case4() {
    int a[] = { 5, -1, -2, 2 };
    int result = maxSum(a, 4);
    mu_assert("error, maxSum(a, 4) != 5", result == 5);
    return 0;
}
static const char* all_tests() {
    mu_run_test(test_case1);
    mu_run_test(test_case2);
    mu_run_test(test_case3);
    mu_run_test(test_case4);
    return 0;
}

int main(int argc, char** argv) {
    const char* result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
