#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *create_node(int value) {
    struct Node *new_node = malloc(sizeof(struct Node));

    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
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
    new_node->prev = current;
}

void display_forward(struct Node *head) {
    printf("Forward: ");

    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }

    printf("NULL\n");
}

void display_backward(struct Node *head) {
    if (head == NULL)
        return;

    while (head->next != NULL)
        head = head->next;

    printf("Backward: ");

    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->prev;
    }

    printf("NULL\n");
}

void delete_value(struct Node **head, int value) {
    struct Node *current = *head;

    while (current != NULL && current->data != value)
        current = current->next;

    if (current == NULL)
        return;

    if (current->prev != NULL)
        current->prev->next = current->next;
    else
        *head = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;

    free(current);
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
    insert_end(&head, 30);

    display_forward(head);
    display_backward(head);

    delete_value(&head, 20);
    display_forward(head);

    free_list(head);

    return 0;
}
