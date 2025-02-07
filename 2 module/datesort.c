#include <stdio.h>
#include <stdlib.h>

#define MAX_DATES 100000

struct Date {
    int Day, Month, Year;
};

void countingSort(struct Date* dates, int n, int maxValue, int (*key)(struct Date)) {
    int count[maxValue + 1];
    struct Date output[n];

    for (int i = 0; i <= maxValue; i++) count[i] = 0;

    for (int i = 0; i < n; i++) {
        count[key(dates[i])]++;
    }

    for (int i = 1; i <= maxValue; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[key(dates[i])] - 1] = dates[i];
        count[key(dates[i])]--;
    }

    for (int i = 0; i < n; i++) {
        dates[i] = output[i];
    }
}

int getYear(struct Date date) {
    return date.Year - 1970;
}

int getMonth(struct Date date) {
    return date.Month - 1;
}

int getDay(struct Date date) {
    return date.Day - 1;
}

void radixSort(struct Date* dates, int n) {
    countingSort(dates, n, 31 - 1, getDay);
    countingSort(dates, n, 12 - 1, getMonth);
    countingSort(dates, n, 2030 - 1970, getYear);
}

int main() {
    int n;
    scanf("%d", &n);

    struct Date dates[MAX_DATES];

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &dates[i].Year, &dates[i].Month, &dates[i].Day);
    }

    radixSort(dates, n);

    for (int i = 0; i < n; i++) {
        printf("%04d %02d %02d\n", dates[i].Year, dates[i].Month, dates[i].Day);
    }

    return 0;
}
