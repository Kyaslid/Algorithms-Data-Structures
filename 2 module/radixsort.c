#include <stdio.h>
#include <stdlib.h>

#define BASE 256

union Int32 {
    int x;
    unsigned char bytes[4];
};

void countingSort(union Int32* arr, int n, int byteIndex, int isSigned) {
    int count[BASE] = {0};
    union Int32 output[n];

    for (int i = 0; i < n; i++) {
        unsigned char key = arr[i].bytes[byteIndex];
        if (isSigned && byteIndex == 3) {
            key ^= 128; // Смещение для обработки знакового байта
        }
        count[key]++;
    }

    for (int i = 1; i < BASE; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        unsigned char key = arr[i].bytes[byteIndex];
        if (isSigned && byteIndex == 3) {
            key ^= 128;
        }
        output[--count[key]] = arr[i];
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(union Int32* arr, int n) {
    for (int byteIndex = 0; byteIndex < 4; byteIndex++) {
        countingSort(arr, n, byteIndex, 1);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    union Int32 arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i].x);
    }

    radixSort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i].x);
    }
    printf("\n");

    return 0;
}
