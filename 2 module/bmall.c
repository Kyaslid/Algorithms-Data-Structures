#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void build_bad_char_table(const char *pattern, int n, int bc[256]) {
    for (int i = 0; i < 256; i++) {
        bc[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        bc[(unsigned char)pattern[i]] = i;
    }
}

static void build_suffix_array(const char *pattern, int n, int *suffix) {
    suffix[n - 1] = n;
    int g = n - 1;
    int f = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (i > g && suffix[i + (n - 1 - f)] < i - g) {
            suffix[i] = suffix[i + (n - 1 - f)];
        } else {
            g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + (n - 1 - f)]) {
                g--;
            }
            suffix[i] = f - g;
        }
    }
}

static void build_good_suffix_table(const char *pattern, int n, int *gs) {
    int *suffix = (int *)malloc(n * sizeof(int));
    build_suffix_array(pattern, n, suffix);
    for (int i = 0; i < n; i++) {
        gs[i] = n;
    }
    int j = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (suffix[i] == i + 1) {
            for (; j < n - 1 - i; j++) {
                if (gs[j] == n) {
                    gs[j] = n - 1 - i;
                }
            }
        }
    }
    for (int i = 0; i < n - 1; i++) {
        gs[n - 1 - suffix[i]] = n - 1 - i;
    }
    free(suffix);
}

static void boyer_moore_search(const char *pattern, const char *text) {
    int n = (int)strlen(pattern);
    int m = (int)strlen(text);
    if (n == 0 || m == 0) return;
    int bc[256];
    int *gs = (int *)malloc(n * sizeof(int));
    build_bad_char_table(pattern, n, bc);
    build_good_suffix_table(pattern, n, gs);
    int i = 0;
    while (i <= m - n) {
        int j = n - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }
        if (j < 0) {
            printf("%d\n", i);
            i += gs[0];
        } else {
            int bcShift = j - bc[(unsigned char)text[i + j]];
            if (bcShift < 1) bcShift = 1;
            int gsShift = gs[j];
            i += (bcShift > gsShift ? bcShift : gsShift);
        }
    }
    free(gs);
}

int main(int argc, char *argv[]) {
    if (argc < 3) return 0;
    boyer_moore_search(argv[1], argv[2]);
    return 0;
}
