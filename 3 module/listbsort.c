#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elem {
    struct Elem *next;
    char *word;
};

char *my_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *dup = malloc(len);
    if (dup) {
        strcpy(dup, str);
    }
    return dup;
}

char *read_line(void) {
    char buffer[1024];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return NULL;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    char *line = malloc(len + 1);
    if (line) {
        strcpy(line, buffer);
    }
    return line;
}

struct Elem *make_list(char *str) {
    struct Elem *head = NULL;
    struct Elem *tail = NULL;
    const char *delim = " \t";
    char *token = strtok(str, delim);
    while (token) {
        struct Elem *new_elem = malloc(sizeof(struct Elem));
        new_elem->word = my_strdup(token);
        new_elem->next = NULL;
        if (!head) {
            head = new_elem;
            tail = new_elem;
        } else {
            tail->next = new_elem;
            tail = new_elem;
        }
        token = strtok(NULL, delim);
    }
    return head;
}

void print_list(struct Elem *list) {
    struct Elem *cur = list;
    while (cur) {
        printf("%s", cur->word);
        if (cur->next) {
            printf(" ");
        }
        cur = cur->next;
    }
    printf("\n");
}

void free_list(struct Elem *list) {
    struct Elem *cur = list;
    while (cur) {
        struct Elem *apex = cur;
        cur = cur->next;
        free(apex->word);
        free(apex);
    }
}

struct Elem *bsort(struct Elem *list) {
    if (!list || !list->next) {
        return list;
    }
    struct Elem *ptr;
    struct Elem *last_ptr = NULL;
    while (1) {
        int swapped = 0;
        ptr = list;
        while (ptr->next != last_ptr) {
            if (strlen(ptr->word) > strlen(ptr->next->word)) {
                char *vrem = ptr->word;
                ptr->word = ptr->next->word;
                ptr->next->word = vrem;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last_ptr = ptr;
        if (!swapped) {
            break;
        }
    }
    return list;
}

int main(void) {
    char *line = read_line();
    struct Elem *list = make_list(line);
    list = bsort(list);
    print_list(list);
    free_list(list);
    free(line);
    return 0;
}
