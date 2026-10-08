#include <stdio.h>

#define MAX_SIZE 100

struct Queue {
    int data[MAX_SIZE];
    int front;
    int rear;
    int size;
};

void init_queue(struct Queue *queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

int is_empty(struct Queue *queue) {
    return queue->size == 0;
}

int is_full(struct Queue *queue) {
    return queue->size == MAX_SIZE;
}

void enqueue(struct Queue *queue, int value) {
    if (is_full(queue)) {
        printf("Queue is full.\n");
        return;
    }

    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->data[queue->rear] = value;
    queue->size++;
}

int dequeue(struct Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }

    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;
    queue->size--;

    return value;
}

int peek(struct Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }

    return queue->data[queue->front];
}

int main(void) {
    struct Queue queue;
    init_queue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("Front: %d\n", peek(&queue));
    printf("Dequeue: %d\n", dequeue(&queue));
    printf("Front after dequeue: %d\n", peek(&queue));

    return 0;
}
