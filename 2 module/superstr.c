#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 10
#define MAX_LEN 1000

int isSubstring(const char *s, const char *t) {
    return strstr(t, s) != NULL;
}

int findShortestSuperstring(char *strings[], int n, char *result) {
    int minLength = MAX_LEN * MAX_N;
    char used[MAX_N];
    char tempResult[MAX_LEN * MAX_N] = "";

    void permute(int level, int length) {
        if (level == n) {
            if (length < minLength) {
                minLength = length;
                strcpy(result, tempResult);
            }
            return;
        }

        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                used[i] = 1;
                int overlap = 0;
                if (level > 0) {
                    for (int j = strlen(strings[i]); j > 0; j--) {
                        if (j <= length && !strncmp(tempResult + length - j, strings[i], j)) {
                            overlap = j;
                            break;
                        }
                    }
                }

                strcpy(tempResult + length - overlap, strings[i]);
                permute(level + 1, length + strlen(strings[i]) - overlap);

                used[i] = 0;
            }
        }
    }

    memset(used, 0, sizeof(used));
    permute(0, 0);

    return minLength;
}

int main() {
    int n;
    char *strings[MAX_N];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        strings[i] = malloc(MAX_LEN + 1);
        scanf("%s", strings[i]);
    }

    char result[MAX_LEN * MAX_N] = "";
    int minLength = findShortestSuperstring(strings, n, result);

    printf("%d\n", minLength);

    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }

    return 0;
}
