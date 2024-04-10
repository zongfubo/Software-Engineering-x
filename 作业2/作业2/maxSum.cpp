#include "maxSum.h"

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
