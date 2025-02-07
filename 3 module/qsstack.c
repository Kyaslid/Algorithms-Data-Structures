#include <stdio.h>
#include <stdlib.h>

struct Task {
    int low;
    int high;
};

int part(int arr[], int low, int high) {
    int elem = arr[high];
    int i = low - 1, t;

    for (int j = low; j < high; j++) {
        if (arr[j] <= elem) {
            i++;
            t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    t = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = t;
    return (i + 1);
}

void qsortIter(int arr[], int n) {
    struct Task *stack = (struct Task*)malloc(n * sizeof(struct Task));
    int top = 0, low, high, elemInd;
    
    stack[top].low = 0;
    stack[top].high = n - 1;
    while (top >= 0) {
        struct Task curTask = stack[top--];
        low = curTask.low;
        high = curTask.high;
        elemInd = part(arr, low, high);
        if (elemInd - 1 > low) {
            stack[++top].low = low;
            stack[top].high = elemInd - 1;
        }
        if (elemInd + 1 < high) {
            stack[++top].low = elemInd + 1;
            stack[top].high = high;
        }
    }
    free(stack);
}

int main(void) {
    int n;
    scanf("%d", &n);
    if(n<1) return 0;

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    qsortIter(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);
    return 0;
}
