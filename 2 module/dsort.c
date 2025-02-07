#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

void countingSort(char* str) {
    int count[ALPHABET_SIZE] = {0};
    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        count[str[i] - 'a']++;
    }

    int index = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        while (count[i]--) {
            str[index++] = i + 'a';
        }
    }
}

int main() {
    char str[1000001];
    scanf("%s", str);

    countingSort(str);

    printf("%s\n", str);

    return 0;
}
