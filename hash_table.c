#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define KEY_SIZE 50

struct Entry {
    char key[KEY_SIZE];
    int value;
    struct Entry *next;
};

struct Entry *table[TABLE_SIZE];

int hash(const char *key) {
    unsigned int sum = 0;

    for (int i = 0; key[i] != '\0'; i++)
        sum += (unsigned char)key[i];

    return sum % TABLE_SIZE;
}

void insert(const char *key, int value) {
    int index = hash(key);

    struct Entry *current = table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }

        current = current->next;
    }

    struct Entry *new_entry = malloc(sizeof(struct Entry));

    if (new_entry == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(new_entry->key, key, KEY_SIZE - 1);
    new_entry->key[KEY_SIZE - 1] = '\0';
    new_entry->value = value;
    new_entry->next = table[index];

    table[index] = new_entry;
}

int search(const char *key, int *value) {
    int index = hash(key);
    struct Entry *current = table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *value = current->value;
            return 1;
        }

        current = current->next;
    }

    return 0;
}

void delete_key(const char *key) {
    int index = hash(key);
    struct Entry *current = table[index];
    struct Entry *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (previous == NULL)
                table[index] = current->next;
            else
                previous->next = current->next;

            free(current);
            return;
        }

        previous = current;
        current = current->next;
    }
}

void display(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);

        struct Entry *current = table[i];

        while (current != NULL) {
            printf("(%s, %d) -> ", current->key, current->value);
            current = current->next;
        }

        printf("NULL\n");
    }
}

void free_table(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Entry *current = table[i];

        while (current != NULL) {
            struct Entry *next = current->next;
            free(current);
            current = next;
        }

        table[i] = NULL;
    }
}

int main(void) {
    insert("Ali", 20);
    insert("Maxime", 25);
    insert("Mohammed", 30);

    display();

    int value;

    if (search("Ali", &value))
        printf("Ali = %d\n", value);

    delete_key("Ali");

    printf("\nAfter deleting Ali:\n");
    display();

    free_table();

    return 0;
}
