#include <stdio.h>

#define MAX_SIZE 100

void display(int a[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("]\n");
}

void insert(int a[], int *n, int index, int value) {
    if (*n >= MAX_SIZE || index < 0 || index > *n)
        return;

    for (int i = *n; i > index; i--)
        a[i] = a[i - 1];

    a[index] = value;
    (*n)++;
}

void delete_at(int a[], int *n, int index) {
    if (index < 0 || index >= *n)
        return;

    for (int i = index; i < *n - 1; i++)
        a[i] = a[i + 1];

    (*n)--;
}

int main(void) {
    int a[MAX_SIZE] = {10, 20, 30, 40};
    int n = 4;

    printf("Array: ");
    display(a, n);

    insert(a, &n, 2, 25);
    printf("After insertion: ");
    display(a, n);

    delete_at(a, &n, 1);
    printf("After deletion: ");
    display(a, n);

    printf("Direct access a[2] = %d\n", a[2]);

    return 0;
}
