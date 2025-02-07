#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 1000000

typedef struct {
    int index;
    int value;
    int is_deleted;
} Element;

typedef struct {
    Element *buckets;
    int capacity;
} HashTable;

int compute_hash(int index, int capacity) {
    return (index % capacity + capacity) % capacity;
}

HashTable* init_hash_table(int capacity) {
    HashTable *table = (HashTable*) malloc(sizeof(HashTable));
    table->buckets = (Element*) malloc(capacity * sizeof(Element));
    table->capacity = capacity;

    for (int i = 0; i < capacity; i++) {
        table->buckets[i].index = -1;
    }

    return table;
}

int get_element(HashTable *table, int index) {
    int hash_index = compute_hash(index, table->capacity);
    int start_index = hash_index;

    while (table->buckets[hash_index].index != -1) {
        if (table->buckets[hash_index].index == index && !table->buckets[hash_index].is_deleted) {
            return table->buckets[hash_index].value;
        }
        hash_index = (hash_index + 1) % table->capacity;
        if (hash_index == start_index) {
            break;
        }
    }
    return 0;
}

void set_element(HashTable *table, int index, int value) {
    int hash_index = compute_hash(index, table->capacity);
    int start_index = hash_index;

    while (table->buckets[hash_index].index != -1 && table->buckets[hash_index].index != index) {
        hash_index = (hash_index + 1) % table->capacity;
        if (hash_index == start_index) {
            return;
        }
    }

    if (value != 0) {
        table->buckets[hash_index].index = index;
        table->buckets[hash_index].value = value;
        table->buckets[hash_index].is_deleted = 0;
    } else {
        table->buckets[hash_index].is_deleted = 1; // Отмечаем элемент как удаленный
    }
}


int main() {
    int capacity;
    scanf("%d", &capacity);
    HashTable *table = init_hash_table(capacity);
    char command[10];
    int index, value;

    while (1) {
        scanf("%s", command);
        if (command[0] == 'E') {
            break;
        }

        if (command[0] == 'A' && command[1] == 'T') {
            scanf("%d", &index);
            printf("%d\n", get_element(table, index));
        } else if (command[0] == 'A' && command[1] == 'S') {
            scanf("%d %d", &index, &value);
            set_element(table, index, value);
        }
    }

    free(table->buckets);
    free(table);
    return 0;
}
