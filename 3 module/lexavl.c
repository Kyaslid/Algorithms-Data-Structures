#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *key;
    int value;
    int height;
    struct Node *left, *right;
} Node;

char *my_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *copy = (char *)malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}

Node *createNode(const char *key, int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = my_strdup(key);
    node->value = value;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

int getHeight(Node *node) {
    if (node) {
        return node->height;
    } else {
        return 0;
    }
}

int getBalance(Node *node) {
    if (node) {
        return getHeight(node->left) - getHeight(node->right);
    } else {
        return 0;
    }
}

Node *rotateRight(Node *y) {
    Node *x = y->left;
    Node *T = x->right;

    x->right = y;
    y->left = T;

    if (getHeight(y->left) > getHeight(y->right)) {
        y->height = 1 + getHeight(y->left);
    } else {
        y->height = 1 + getHeight(y->right);
    }

    if (getHeight(x->left) > getHeight(x->right)) {
        x->height = 1 + getHeight(x->left);
    } else {
        x->height = 1 + getHeight(x->right);
    }

    return x;
}

Node *rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T = y->left;

    y->left = x;
    x->right = T;

    if (getHeight(x->left) > getHeight(x->right)) {
        x->height = 1 + getHeight(x->left);
    } else {
        x->height = 1 + getHeight(x->right);
    }

    if (getHeight(y->left) > getHeight(y->right)) {
        y->height = 1 + getHeight(y->left);
    } else {
        y->height = 1 + getHeight(y->right);
    }

    return y;
}

Node *insert(Node *node, const char *key, int value, int *insertedValue) {
    if (!node) {
        *insertedValue = value;
        return createNode(key, value);
    }

    if (strcmp(key, node->key) < 0) {
        node->left = insert(node->left, key, value, insertedValue);
    } else if (strcmp(key, node->key) > 0) {
        node->right = insert(node->right, key, value, insertedValue);
    } else {
        *insertedValue = node->value;
        return node;
    }

    if (getHeight(node->left) > getHeight(node->right)) {
        node->height = 1 + getHeight(node->left);
    } else {
        node->height = 1 + getHeight(node->right);
    }

    int balance = getBalance(node);

    if (balance > 1 && strcmp(key, node->left->key) < 0)
        return rotateRight(node);

    if (balance < -1 && strcmp(key, node->right->key) > 0)
        return rotateLeft(node);

    if (balance > 1 && strcmp(key, node->left->key) > 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && strcmp(key, node->right->key) < 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void freeTree(Node *node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        free(node->key);
        free(node);
    }
}

void analyzeString(const char *str) {
    Node *tree = NULL;
    int identifierIndex = 0;

    for (const char *p = str; *p;) {
        while (isspace(*p)) p++;

        if (isdigit(*p)) {
            long value = 0;
            while (isdigit(*p)) {
                value = value * 10 + (*p - '0');
                p++;
            }
            printf("CONST %ld\n", value);
        } else if (strchr("+-*/()", *p)) {
            printf("SPEC %d\n", (int)(strchr("+-*/()", *p) - "+-*/()"));
            p++;
        } else if (isalpha(*p)) {
            char buffer[256];
            int i = 0;
            while (isalnum(*p)) {
                buffer[i++] = *p++;
            }
            buffer[i] = '\0';

            int value;
            tree = insert(tree, buffer, identifierIndex, &value);
            if (value == identifierIndex) {
                identifierIndex++;
            }
            printf("IDENT %d\n", value);
        } else {
            p++;
        }
    }

    freeTree(tree);
}

int main() {
    int n;
    scanf("%d", &n);
    getchar();

    char *input = (char *)malloc(n + 1);
    fgets(input, n + 1, stdin);

    analyzeString(input);

    free(input);
    return 0;
}
