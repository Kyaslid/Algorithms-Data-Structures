#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *my_strdup(const char *s) {
    size_t length = strlen(s) + 1;
    char *duplicate = (char *)malloc(length);
    if (duplicate) {
        strcpy(duplicate, s);
    }
    return duplicate;
}

char *concat(char *q, char *d, int n) {
    char *s[2];
    s[0] = q;
    s[1] = d;
    size_t length = 0;
    for (int i = 0; i < n; i++) {
        length += strlen(s[i]);
    }

    char *res = (char *)malloc(length + 1); 

    int res_index = 0;
    for (int i = 0; i < n; ++i) {
        int index = 0;
        while (s[i][index] != '\0') {
            res[res_index] = s[i][index];
            res_index++;
            index++;
        }
    }
    res[res_index] = '\0';
    return res;
}

char *fibstr(int n) {
    if (n == 1) return my_strdup("a");
    if (n == 2) return my_strdup("b");

    char **mass = (char **)malloc(n * sizeof(char *));
    
    mass[0] = my_strdup("a");
    mass[1] = my_strdup("b");

    for (int i = 2; i < n; ++i) {
        mass[i] = concat(mass[i-2], mass[i-1], 2);
        free(mass[i-2]); // Освобождаем ранее использованную строку
    }

    char *result = my_strdup(mass[n-1]);
    free(mass[n-2]); // освобождаем предпоследний элемент
    free(mass[n-1]);
    free(mass);

    return result;
}


int main() {
    int n;
    scanf("%d", &n);
    
    char *fib_result = fibstr(n);
    if (fib_result) {
        printf("%s\n", fib_result);
        free(fib_result);
    }

    return 0;
}
