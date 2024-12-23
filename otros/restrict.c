#include <stdio.h>

void suma_arrays(int *restrict arr1, int *restrict arr2, int *restrict result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = arr1[i] + arr2[i];
    }
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, 20, 30, 40, 50};
    int result[5];

    suma_arrays(arr1, arr2, result, 5);

    for (int i = 0; i < 5; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}
