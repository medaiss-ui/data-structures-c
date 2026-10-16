#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, end;

int fibonacci(int n)
{
    if (n == 0 || n == 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int dp_fibonacci(int n, int *t)
{
    if (n <= 1)
        return n;

    if (t[n] != -1)
        return t[n];

    t[n] = dp_fibonacci(n - 1, t) + dp_fibonacci(n - 2, t);
    return t[n];
}

int main(void)
{
    printf("Enter the value of n: ");
    int n;

    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Please enter a non-negative integer.\n");
        return 1;
    }

    clock_t start = clock();
    int x = fibonacci(n);
    clock_t end = clock();
    double time_naive = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Naive: F(%d) = %d, time = %f seconds\n", n, x, time_naive);

    start = clock();
    int *t = (int *)malloc((n + 1) * sizeof(int));
    if (t == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i <= n; i++)
        t[i] = -1;

    int y = dp_fibonacci(n, t);
    end = clock();
    double time_dp = (double)(end - start) / CLOCKS_PER_SEC;
    printf("DP: F(%d) = %d, time = %f seconds\n", n, y, time_dp);

    free(t);
    return 0;
}
