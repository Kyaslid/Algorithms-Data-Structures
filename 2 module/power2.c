#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 24
#define MIN_VAL -1000000
#define MAX_VAL 1000000

int isPowerOfTwo(int x) {
    return (x > 0) && ((x & (x - 1)) == 0);
}

void countPowerOfTwoSums(int *arr, int n, int *count) {
    int totalCombinations = 1 << n;
    for (int mask = 1; mask < totalCombinations; mask++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += arr[i];
            }
        }
        if (isPowerOfTwo(sum)) {
            (*count)++;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int count = 0;
    countPowerOfTwoSums(arr, n, &count);

    printf("%d\n", count);
    return 0;
}
