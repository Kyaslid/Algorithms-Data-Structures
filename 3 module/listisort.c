#include <stdio.h>
#include <stdlib.h>

struct Elem {
    struct Elem *prev, *next;
    int v;
};

struct Elem* createList(int n, int *arr) {
    if (n <= 0) return NULL;
    struct Elem* head = (struct Elem*)malloc(sizeof(struct Elem));
    head->v = arr[0];
    head->prev = head;
    head->next = head;
    struct Elem* last = head;
    for (int i = 1; i < n; i++) {
        struct Elem* node = (struct Elem*)malloc(sizeof(struct Elem));
        node->v = arr[i];
        node->next = head;
        node->prev = last;
        last->next = node;
        head->prev = node;
        last = node;
    }
    return head;
}

void printList(struct Elem *head) {
    if (!head) return;
    struct Elem *cur = head;
    do {
        printf("%d ", cur->v);
        cur = cur->next;
    } while (cur != head);
    printf("\n");
}

void freeList(struct Elem *head) {
    if (!head) return;
    struct Elem *cur = head->next;
    while (cur != head) {
        struct Elem *vrem = cur;
        cur = cur->next;
        free(vrem);
    }
    free(head);
}

void removeNode(struct Elem *node) {
    if (!node) return;
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
}

struct Elem* insertionSortDoubly(struct Elem* head) {
    if (!head || !head->next) return head;
    struct Elem* sorted = head;
    struct Elem* cur = head->next;
    sorted->next = NULL;
    sorted->prev = NULL;
    while (cur) {
        struct Elem* next = cur->next;
        cur->prev = NULL;
        cur->next = NULL;
        if (cur->v < sorted->v) {
            cur->next = sorted;
            sorted->prev = cur;
            sorted = cur;
        } else {
            struct Elem* p = sorted;
            while (p->next && p->next->v < cur->v) {
                p = p->next;
            }
            cur->next = p->next;
            if (p->next) p->next->prev = cur;
            p->next = cur;
            cur->prev = p;
        }
        cur = next;
    }
    return sorted;
}

struct Elem* insertionSort(struct Elem *head) {
    if (!head || head->next == head) return head;
    struct Elem* tail = head->prev;
    tail->next = NULL;
    head->prev = NULL;
    struct Elem* newHead = insertionSortDoubly(head);
    struct Elem* newTail = newHead;
    while (newTail->next) {
        newTail = newTail->next;
    }
    newTail->next = newHead;
    newHead->prev = newTail;
    return newHead;
}

int main() {
    int n;
    scanf("%d", &n);
    if (n <= 0) return 0;
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    struct Elem *head = createList(n, arr);
    head = insertionSort(head);
    printList(head);
    freeList(head);
    free(arr);
    return 0;
}
