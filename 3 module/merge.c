#include <stdio.h>
#include <stdlib.h>

struct GlobalElem {
    int val;
};

struct QItem {
    int value;
    int whichArr;
    int offset;
};

static void swapQ(struct QItem* a, struct QItem* b) {
    struct QItem vrem = *a;
    *a = *b;
    *b = vrem;
}

static void siftDown(struct QItem* heap, int size, int root) {
    while (1) {
        int left = 2 * root + 1;
        int right = 2 * root + 2;
        int smallest = root;
        if (left < size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        if (smallest == root) {
            break;
        }
        swapQ(&heap[root], &heap[smallest]);
        root = smallest;
    }
}

static void siftUp(struct QItem* heap, int idx) {
    while (idx > 0) {
        int par = (idx - 1) / 2;
        if (heap[idx].value >= heap[par].value) {
            break;
        }
        swapQ(&heap[idx], &heap[par]);
        idx = par;
    }
}

static struct QItem popMin(struct QItem* heap, int* heapSize) {
    struct QItem top = heap[0];
    heap[0] = heap[*heapSize - 1];
    (*heapSize)--;
    siftDown(heap, *heapSize, 0);
    return top;
}

static void pushHeap(struct QItem* heap, int* heapSize, struct QItem x) {
    heap[*heapSize] = x;
    (*heapSize)++;
    siftUp(heap, (*heapSize) - 1);
}

int main(void) {
    int k;
    scanf("%d", &k);
    int* sizes = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        scanf("%d", &sizes[i]);
    }
    int n = 0;
    for (int i = 0; i < k; i++) {
        n += sizes[i];
    }
    struct GlobalElem* gArr = (struct GlobalElem*)malloc(n * sizeof(struct GlobalElem));
    int* startPos = (int*)malloc(k * sizeof(int));
    startPos[0] = 0;
    for (int i = 1; i < k; i++) {
        startPos[i] = startPos[i - 1] + sizes[i - 1];
    }
    for (int i = 0; i < k; i++) {
        int base = startPos[i];
        for (int j = 0; j < sizes[i]; j++) {
            scanf("%d", &gArr[base + j].val);
        }
    }
    struct QItem* heap = (struct QItem*)malloc(k * sizeof(struct QItem));
    int heapSize = 0;
    for (int i = 0; i < k; i++) {
        if (sizes[i] > 0) {
            struct QItem node;
            node.value = gArr[startPos[i]].val;
            node.whichArr = i;
            node.offset = 0;
            pushHeap(heap, &heapSize, node);
        }
    }
    for (int count = 0; count < n; count++) {
        struct QItem top = popMin(heap, &heapSize);
        printf("%d ", top.value);
        int arrID = top.whichArr;
        int pos = top.offset + 1;
        if (pos < sizes[arrID]) {
            struct QItem next;
            next.value = gArr[startPos[arrID] + pos].val;
            next.whichArr = arrID;
            next.offset = pos;
            pushHeap(heap, &heapSize, next);
        }
    }
    printf("\n");
    free(heap);
    free(gArr);
    free(startPos);
    free(sizes);
    return 0;
}
