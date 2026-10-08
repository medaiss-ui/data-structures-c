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

void insert_end(struct Node **head, int value) {
    struct Node *new_node = create_node(value);

    if (*head == NULL) {
        *head = new_node;
        new_node->next = *head;
        return;
    }

    struct Node *current = *head;

    while (current->next != *head)
        current = current->next;

    current->next = new_node;
    new_node->next = *head;
}

void display(struct Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *current = head;

    printf("Circular list: ");

    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != head);

    printf("(back to head)\n");
}

void delete_value(struct Node **head, int value) {
    if (*head == NULL)
        return;

    struct Node *current = *head;
    struct Node *previous = NULL;

    do {
        if (current->data == value)
            break;

        previous = current;
        current = current->next;
    } while (current != *head);

    if (current->data != value)
        return;

    if (current == *head) {
        if (current->next == *head) {
            *head = NULL;
            free(current);
            return;
        }

        struct Node *last = *head;

        while (last->next != *head)
            last = last->next;

        *head = current->next;
        last->next = *head;
        free(current);
        return;
    }

    previous->next = current->next;
    free(current);
}

void free_list(struct Node **head) {
    if (*head == NULL)
        return;

    struct Node *current = (*head)->next;

    while (current != *head) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }

    free(*head);
    *head = NULL;
}

int main(void) {
    struct Node *head = NULL;

    insert_end(&head, 10);
    insert_end(&head, 20);
    insert_end(&head, 30);

    display(head);

    delete_value(&head, 20);
    display(head);

    free_list(&head);

    return 0;
}
