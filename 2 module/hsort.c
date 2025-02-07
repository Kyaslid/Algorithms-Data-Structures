#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_a(const char *str) {
    int count = 0;
    while (*str) {
        if (*str == 'a') {  // Считаем только символы 'a'
            count++;
        }
        str++;
    }
    return count;
}

int compare_strings(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    int count1 = count_a(str1);
    int count2 = count_a(str2);

    // Сортировка по количеству 'a', если количество одинаково — порядок сохраняется
    if (count1 != count2) {
        return count1 - count2;  // Возвращаем разницу в количестве 'a'
    }
    return 0;  // Если количество одинаково, порядок не меняется
}

void hsort(void *base, size_t nel, size_t width,
           int (*compare)(const void *a, const void *b)) {
    // Функция для обмена элементов
    void swap(void *a, void *b, size_t width) {
        unsigned char *x = a, *y = b, temp;
        for (size_t i = 0; i < width; i++) {
            temp = x[i];
            x[i] = y[i];
            y[i] = temp;
        }
    }

    // Функция для восстановления пирамиды
    void heapify(void *base, size_t nel, size_t width, size_t root,
                 int (*compare)(const void *a, const void *b)) {
        size_t largest = root;
        size_t left = 2 * root + 1;
        size_t right = 2 * root + 2;

        void *base_root = (unsigned char *)base + root * width;
        void *base_left = (unsigned char *)base + left * width;
        void *base_right = (unsigned char *)base + right * width;

        if (left < nel && compare(base_left, base_root) > 0) {
            largest = left;
        }

        if (right < nel && compare((unsigned char *)base + largest * width, base_right) < 0) {
            largest = right;
        }

        if (largest != root) {
            swap((unsigned char *)base + root * width, (unsigned char *)base + largest * width, width);
            heapify(base, nel, width, largest, compare);
        }
    }

    // Построение пирамиды
    for (size_t i = nel / 2; i > 0; i--) {
        heapify(base, nel, width, i - 1, compare);
    }

    // Сортировка пирамиды
    for (size_t i = nel; i > 1; i--) {
        swap(base, (unsigned char *)base + (i - 1) * width, width);
        heapify(base, i - 1, width, 0, compare);
    }
}

int main() {
    size_t n;
    scanf("%zu", &n);

    char buffer[1000];
    char *strings[n];

    for (size_t i = 0; i < n; i++) {
        scanf("%s", buffer);
        strings[i] = malloc(strlen(buffer) + 1);
        strcpy(strings[i], buffer);
    }

    hsort(strings, n, sizeof(char *), compare_strings);

    for (size_t i = 0; i < n; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]);
    }

    return 0;
}
