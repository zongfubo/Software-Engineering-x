#include<stdio.h>
#include<stdlib.h>

int maxSum(int a[], int size) {
    int Far = 0, Here = 0;

    for (int i = 0; i < size; i++) {
        Here = Here + a[i];
        if (Here < 0)
            Here = 0;
        if (Far < Here)
            Far = Here;
    }
    return Far;
}

int main() {
    int n;
    printf("请输入整数的数量 n: ");
    scanf_s("%d", &n);
    int* a = (int*)malloc(n * sizeof(int));
    printf("请输入%d个整数：\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf_s("%d", &a[i]);
    }
    int max_sum = maxSum(a, n);
    printf("最大子段和为 %d\n", max_sum);
    return 0;
}
//测试：-2, 11, -4, 13, -5, -2