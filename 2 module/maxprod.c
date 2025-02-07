#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    int n;
    scanf("%d", &n);
    double *logs = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d/%d", &a, &b);
        if (a == 0) {
            logs[i] = -INFINITY;
        } else {
            logs[i] = log((double)a) - log((double)b);
        }
    }
    double maxSum = -INFINITY;
    int maxL = 0, maxR = 0;
    double Sum = 0.0;
    int Start = 0;

    for (int i = 0; i < n; i++) {
        if (!isfinite(logs[i])) {
            double product = 0.0;
            double best = exp(maxSum);
            if (product > best) {
                maxSum = log(product);
                maxL = i;
                maxR = i;
            }
            Sum = 0.0;
            Start = i + 1;
        } else {
            if (Sum + logs[i] < logs[i]) {
                Sum = logs[i];
                Start = i;
            } else {
                Sum += logs[i];
            }
            if (Sum > maxSum) {
                maxSum = Sum;
                maxL = Start;
                maxR = i;
            }
        }
    }
    free(logs);
    printf("%d %d\n", maxL, maxR);
    return 0;
}
