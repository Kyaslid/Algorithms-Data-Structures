#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long gcd_ll(long long x, long long y) {
    if (x < 0) x = -x;
    if (y < 0) y = -y;
    while (y != 0) {
        long long t = x % y;
        x = y;
        y = t;
    }
    return x;
}

int main(void) {
    int n;
    scanf("%d", &n);
    long long *arr = (long long *)malloc(n * sizeof(long long));

    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }
    int *log2val = (int *)malloc((n + 1) * sizeof(int));
    log2val[1] = 0;
    
    for (int i = 2; i <= n; i++) {
        log2val[i] = log2val[i / 2] + 1;
    }
    int maxK = log2val[n];
    long long **st = (long long **)malloc((maxK + 1) * sizeof(long long *));
    for (int k = 0; k <= maxK; k++) {
        st[k] = (long long *)malloc(n * sizeof(long long));
    }

    for (int i = 0; i < n; i++) {
        st[0][i] = arr[i];
    }

    for (int k = 1; k <= maxK; k++) {
        int step = 1 << (k - 1);
        for (int i = 0; i + (1 << k) - 1 < n; i++) {
            st[k][i] = gcd_ll(st[k - 1][i], st[k - 1][i + step]);
        }
    }
    free(arr);
    int m;
    scanf("%d", &m);

    for(int im=0;im<m;im++) {
        int l, r;
        if (scanf("%d %d", &l, &r) != 2) {
            break;
        }
        if (l > r) {
            int tmp = l;
            l = r;
            r = tmp;
        }
        int length = r - l + 1;
        int k = log2val[length];
        long long g = gcd_ll(st[k][l], st[k][r - (1 << k) + 1]);
        printf("%lld\n", g);
    }
    for (int k = 0; k <= maxK; k++) {
        free(st[k]);
    }
    free(st);
    free(log2val);
    return 0;
}
