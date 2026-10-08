#include <stdio.h>

#define MAX_SIZE 100

struct Stack {
    int data[MAX_SIZE];
    int top;
};

void init_stack(struct Stack *stack) {
    stack->top = -1;
}

int is_empty(struct Stack *stack) {
    return stack->top == -1;
}

int is_full(struct Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(struct Stack *stack, int value) {
    if (is_full(stack)) {
        printf("Stack overflow.\n");
        return;
    }

    stack->data[++stack->top] = value;
}

int pop(struct Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack underflow.\n");
        return -1;
    }

    return stack->data[stack->top--];
}

int peek(struct Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }

    return stack->data[stack->top];
}

int main(void) {
    struct Stack stack;
    init_stack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top: %d\n", peek(&stack));
    printf("Pop: %d\n", pop(&stack));
    printf("Top after pop: %d\n", peek(&stack));

    return 0;
}
