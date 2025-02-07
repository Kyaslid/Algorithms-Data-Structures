#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void computeLPS(const char *S, int *lps, int n) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < n) {
        if (S[i] == S[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 0;
    }

    const char *S = argv[1];
    const char *T = argv[2];

    int n = strlen(S);
    int m = strlen(T);

    if (n == 0 || m == 0) {
        return 0;
    }

    int *lps = (int *)malloc(n * sizeof(int));
    computeLPS(S, lps, n);

    int i = 0;
    int j = 0;
    while (i < m) {
        if (T[i] == S[j]) {
            i++;
            j++;
            if (j == n) {
                printf("%d\n", i - j);
                j = lps[j - 1];
            }
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    return 0;
}
