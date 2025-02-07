#include <stdio.h>
#include <stdlib.h>


void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && abs(arr[j]) > abs(key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


void merge(int arr[], int left, int mid, int right) {
    int n = right - left + 1;
    int vrem[n];
    int i = left;
    int j = mid + 1;
    int h = 0;

    while (h < n) {
        if (j > right || (i <= mid && abs(arr[i]) <= abs(arr[j]))) {
            vrem[h] = arr[i];
            i++;
        } else {
            vrem[h] = arr[j];
            j++;
        }
        h++;
    }

    for (int t = 0; t < n; t++) {
        arr[left + t] = vrem[t];
    }
}

void mergeSort(int arr[], int left, int right) {
    if (right - left + 1 < 5) {
        insertionSort(arr, left, right);
    } else {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);       
        mergeSort(arr, mid + 1, right);  
        merge(arr, left, mid, right);    
    }
}

int main() {
    int n;
    scanf("%d", &n); 

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    
    mergeSort(arr, 0, n - 1);

    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
