#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100000

int main(void) {
    int stack[MAX_STACK_SIZE];
    int top = -1;
    char command[16];

    while (1) {
        if (scanf("%s", command) != 1) {
            return 1;
        }
        if (strcmp(command, "CONST") == 0) {
            long long x;
            if (scanf("%lld", &x) != 1) {
                return 1;
            }
            stack[++top] = (int)x;
        }
        else if (strcmp(command, "ADD") == 0) {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = a + b;
        }
        else if (strcmp(command, "SUB") == 0) {
            int a = stack[top--];
            int b = stack[top--];
            stack[++top] = a - b;
        }
        else if (strcmp(command, "MUL") == 0) {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = a * b;
        }
        else if (strcmp(command, "DIV") == 0) {
            int a = stack[top--];
            int b = stack[top--];
            stack[++top] = a / b;
        }
        else if (strcmp(command, "MAX") == 0) {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = (a > b ? a : b);
        }
        else if (strcmp(command, "MIN") == 0) {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = (a < b ? a : b);
        }
        else if (strcmp(command, "NEG") == 0) {
            stack[top] = -stack[top];
        }
        else if (strcmp(command, "DUP") == 0) {
            int val = stack[top];
            stack[++top] = val;
        }
        else if (strcmp(command, "SWAP") == 0) {
            int a = stack[top];
            int b = stack[top - 1];
            stack[top] = b;
            stack[top - 1] = a;
        }
        else if (strcmp(command, "END") == 0) {
            printf("%d\n", stack[top]);
            return 0;
        }
        else {
            return 1;
        }
    }
    return 0;
}
