#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int *data;
    size_t front;
    size_t rear;
    size_t capacity;
} CircularQueue;

void InitQueue(CircularQueue *q) {
    q->capacity = 4;
    q->data = (int *)malloc(q->capacity * sizeof(int));
    q->front = 0;
    q->rear = 0;
}

bool IsEmpty(const CircularQueue *q) {
    return q->front == q->rear;
}

bool IsFull(const CircularQueue *q) {
    return (q->rear + 1) % q->capacity == q->front;
}

void ExpandQueue(CircularQueue *q) {
    size_t newCapacity = q->capacity * 2;
    int *newData = (int *)malloc(newCapacity * sizeof(int));

    size_t i = 0;
    for (size_t index = q->front; index != q->rear; index = (index + 1) % q->capacity) {
        newData[i++] = q->data[index];
    }

    free(q->data);
    q->data = newData;
    q->front = 0;
    q->rear = i;
    q->capacity = newCapacity;
}

void Enqueue(CircularQueue *q, int value) {
    if (IsFull(q)) {
        ExpandQueue(q);
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % q->capacity;
}

int Dequeue(CircularQueue *q) {
    int value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    return value;
}

void FreeQueue(CircularQueue *q) {
    free(q->data);
}

int main() {
    CircularQueue q;
    InitQueue(&q);

    char command[16];
    while (1) {
        scanf("%15s", command);

        if (strcmp(command, "ENQ") == 0) {
            int value;
            scanf("%d", &value);
            Enqueue(&q, value);
        } else if (strcmp(command, "DEQ") == 0) {
            printf("%d\n", Dequeue(&q));
        } else if (strcmp(command, "EMPTY") == 0) {
            printf(IsEmpty(&q) ? "true\n" : "false\n");
        } else if (strcmp(command, "END") == 0) {
            break;
        }
    }

    FreeQueue(&q);
    return 0;
}
