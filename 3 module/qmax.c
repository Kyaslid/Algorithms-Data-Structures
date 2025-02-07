#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Stack {
    long long value;
    long long currentMax;
    struct Stack *next;
} Stack;

typedef struct {
    Stack *top;
} MaxStack;

void initStack(MaxStack *st) {
    st->top = NULL;
}

bool emptyStack(const MaxStack *st) {
    return (st->top == NULL);
}

long long getMax(const MaxStack *st) {
    return st->top->currentMax;
}

void push(MaxStack *st, long long x) {
    Stack *newNode = (Stack *)malloc(sizeof(Stack));

    newNode->value = x;
    if (emptyStack(st)) {
        newNode->currentMax = x;
    } else {
        long long current = getMax(st);
        newNode->currentMax = (x > current) ? x : current;
    }
    newNode->next = st->top;
    st->top = newNode;
}

long long pop(MaxStack *st) {
    Stack *node = st->top;
    long long val = node->value;
    st->top = node->next;
    free(node);
    return val;
}

void freeStack(MaxStack *st) {
    while (!emptyStack(st)) {
        pop(st);
    }
}

typedef struct {
    MaxStack sEnq;
    MaxStack sDeq;
} MaxQueue;

void initQueue(MaxQueue *q) {
    initStack(&(q->sEnq));
    initStack(&(q->sDeq));
}

bool queueEmpty(const MaxQueue *q) {
    return emptyStack(&(q->sEnq)) && emptyStack(&(q->sDeq));
}

void enqueue(MaxQueue *q, long long x) {
    push(&(q->sEnq), x);
}

void shiftStacks(MaxQueue *q) {
    if (emptyStack(&(q->sDeq))) {
        while (!emptyStack(&(q->sEnq))) {
            long long val = pop(&(q->sEnq));
            push(&(q->sDeq), val);
        }
    }
}

long long dequeue(MaxQueue *q) {
    shiftStacks(q);
    return pop(&(q->sDeq));
}

long long queueMax(const MaxQueue *q) {
    bool enqEmpty = emptyStack(&(q->sEnq));
    bool deqEmpty = emptyStack(&(q->sDeq));
    if (!enqEmpty && !deqEmpty) {
        long long m1 = getMax(&(q->sEnq));
        long long m2 = getMax(&(q->sDeq));
        return (m1 > m2) ? m1 : m2;
    } else if (!enqEmpty) {
        return getMax(&(q->sEnq));
    } else {
        return getMax(&(q->sDeq));
    }
}

void freeQueue(MaxQueue *q) {
    freeStack(&(q->sEnq));
    freeStack(&(q->sDeq));
}

int main(void) {
    MaxQueue q;
    initQueue(&q);

    char cmd[16];
    while (1) {
        if (scanf("%s", cmd) != 1) {
            break;
        }
        if (strcmp(cmd, "ENQ") == 0) {
            long long x;
            if (scanf("%lld", &x) != 1) {
                break;
            }
            enqueue(&q, x);
        }
        else if (strcmp(cmd, "DEQ") == 0) {
            long long val = dequeue(&q);
            printf("%lld\n", val);
        }
        else if (strcmp(cmd, "MAX") == 0) {
            long long m = queueMax(&q);
            printf("%lld\n", m);
        }
        else if (strcmp(cmd, "EMPTY") == 0) {
            bool isEmpty = queueEmpty(&q);
            printf("%s\n", isEmpty ? "true" : "false");
        }
        else if (strcmp(cmd, "END") == 0) {
            break;
        }
        else {
            break;
        }
    }

    freeQueue(&q);
    return 0;
}
