#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Node {
    int start;
    int end;
    int max_val;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int start, int end, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->start = start;
    node->end = end;
    node->max_val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* build_segment_tree(int start, int end, int* readCount, int n) {
    if (start == end) {
        int val;
        scanf("%d", &val);
        (*readCount)++;
        Node* leaf = create_node(start, end, val);
        return leaf;
    }
    int mid = (start + end) / 2;
    Node* leftChild = build_segment_tree(start, mid, readCount, n);
    Node* rightChild = build_segment_tree(mid + 1, end, readCount, n);
    if(leftChild->max_val > rightChild->max_val){
        Node* root = create_node(start, end, leftChild->max_val);
        root->left = leftChild;
        root->right = rightChild;
        return root;
    } else {
        Node* root = create_node(start, end, rightChild->max_val);
        root->left = leftChild;
        root->right = rightChild;
        return root;
    }
}

void recalc(Node* node) {
    if (!node->left && !node->right) return;
    int leftVal = node->left ? node->left->max_val : INT_MIN;
    int rightVal = node->right ? node->right->max_val : INT_MIN;
    node->max_val = (leftVal > rightVal ? leftVal : rightVal);
}

void update(Node* root, int idx, int newVal) {
    if (root->start == root->end) {
        root->max_val = newVal;
        return;
    }
    int mid = (root->start + root->end) / 2;
    if (idx <= mid) update(root->left, idx, newVal);
    else update(root->right, idx, newVal);
    recalc(root);
}

int query_max(Node* root, int l, int r) {
    if (root->end < l || root->start > r) return INT_MIN;
    if (l <= root->start && root->end <= r) return root->max_val;
    int leftMax = query_max(root->left, l, r);
    int rightMax = query_max(root->right, l, r);
    return (leftMax > rightMax ? leftMax : rightMax);
}

void free_tree(Node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    int n;
    scanf("%d", &n);
    if (n == 0) {
        char cmd[8];
        while (scanf("%s", cmd) == 1) {
            if (!strcmp(cmd, "END")) break;
        }
        return 0;
    }
    int readCount = 0;
    Node* root = build_segment_tree(1, n, &readCount, n);
    while (1) {
        char command[8];
        if (scanf("%s", command) != 1) break;
        if (!strcmp(command, "END")) break;
        else if (!strcmp(command, "MAX")) {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%d\n", query_max(root, l+1, r+1));
        } else if (!strcmp(command, "UPD")) {
            int i, v;
            scanf("%d %d", &i, &v);
            update(root, i+1, v);
        }
    }
    free_tree(root);
    return 0;
}
