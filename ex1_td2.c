#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

bool is_sorted_increasing(int A[], int n) {
    if (n <= 1) {
        return true;
    }
    for (int i = 1; i < n; i++) {
        if (A[i] <= A[i - 1]) {
            return false;
        }
    }
    return true;
}

int linear_search(int A[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (A[i] == x) {
            return i;
        }
    }
    return -1;
}

int min(int a, int b) {
    if (a <= b) return a;
    return b;
}

int jump_search(int A[], int n, int x) {
    if (!is_sorted_increasing(A, n)) {
        return -1;
    }

    if (n == 0) {
        return -1;
    }

    int step = (int)sqrt(n);
    int prev = 0;

    while (A[min(n, step) - 1] < x) {
        prev = step;
        step += (int)sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }

    int limit = step < n ? step : n;
    for (int i = prev; i < limit; i++) {
        if (A[i] == x) {
            return i;
        }
    }

    return -1;
}

int binary_search_iterative(int A[], int n, int x) {
    if (!is_sorted_increasing(A, n)) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = (int)(high + low) / 2;

        if (A[mid] == x) {
            return mid;
        } else if (A[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

void benchmark() {
    int sizes[] = {1000, 10000, 100000, 1000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("%-10s %-15s %-15s %-15s\n", "Size (n)", "Linear (s)", "Jump (s)", "Binary (s)");
    printf("-----------------------------------------------------------\n");

    for (int k = 0; k < num_sizes; k++) {
        int n = sizes[k];
        int *A = (int *)malloc(n * sizeof(int));

        if (A == NULL) {
            printf("Memory allocation failed for n = %d\n", n);
            return;
        }

        for (int i = 0; i < n; i++) {
            A[i] = i * 2;
        }

        int target = -1;

        clock_t start = clock();
        linear_search(A, n, target);
        double t_linear = (double)(clock() - start) / CLOCKS_PER_SEC;

        start = clock();
        jump_search(A, n, target);
        double t_jump = (double)(clock() - start) / CLOCKS_PER_SEC;

        start = clock();
        binary_search_iterative(A, n, target);
        double t_binary = (double)(clock() - start) / CLOCKS_PER_SEC;

        printf("%-10d %-15.6f %-15.6f %-15.6f\n", n, t_linear, t_jump, t_binary);

        free(A);
    }
}

int main(void) {
    benchmark();
    return 0;
}
