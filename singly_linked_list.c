#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int value) {
    struct Node *new_node = malloc(sizeof(struct Node));

    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}

void insert_front(struct Node **head, int value) {
    struct Node *new_node = create_node(value);

    new_node->next = *head;
    *head = new_node;
}

void insert_end(struct Node **head, int value) {
    struct Node *new_node = create_node(value);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    struct Node *current = *head;

    while (current->next != NULL)
        current = current->next;

    current->next = new_node;
}

int search(struct Node *head, int value) {
    while (head != NULL) {
        if (head->data == value)
            return 1;
        head = head->next;
    }

    return 0;
}

void delete_value(struct Node **head, int value) {
    struct Node *current = *head;
    struct Node *previous = NULL;

    while (current != NULL && current->data != value) {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
        return;

    if (previous == NULL)
        *head = current->next;
    else
        previous->next = current->next;

    free(current);
}

void display(struct Node *head) {
    printf("List: ");

    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }

    printf("NULL\n");
}

void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    struct Node *head = NULL;

    insert_end(&head, 10);
    insert_end(&head, 20);
    insert_front(&head, 5);

    display(head);

    printf("Search 20: %s\n", search(head, 20) ? "found" : "not found");

    delete_value(&head, 10);
    display(head);

    free_list(head);

    return 0;
}
