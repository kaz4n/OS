#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

// Structure to hold the generated Fibonacci series and its length
struct FibResult {
    int *series;
    int length;
};

// Thread function: generates Fibonacci numbers until the term is >= limit
void *fibonacciGenerator(void *arg) {
    int limit = (int)(intptr_t)arg;
    int *series = NULL;
    int length = 0;
    int capacity = 2;

    // Allocate initial capacity
    series = (int*)malloc(capacity * sizeof(int));
    if (series == NULL) {
        perror("malloc");
        pthread_exit(NULL);
    }

    // First Fibonacci term
    series[length++] = 0;
    if (limit > 0) {
        // Second term
        if (length == capacity) {
            capacity *= 2;
            series = (int*)realloc(series, capacity * sizeof(int));
            if (series == NULL) {
                perror("realloc");
                pthread_exit(NULL);
            }
        }
        series[length++] = 1;
    }

    int a = 0, b = 1, next;
    // Generate until the last term >= limit
    while (b < limit) {
        next = a + b;
        // Add the new term
        if (length == capacity) {
            capacity *= 2;
            series = (int*)realloc(series, capacity * sizeof(int));
            if (series == NULL) {
                perror("realloc");
                pthread_exit(NULL);
            }
        }
        series[length++] = next;
        a = b;
        b = next;
    }

    // Prepare the result structure
    struct FibResult *res = (struct FibResult*)malloc(sizeof(struct FibResult));
    if (res == NULL) {
        perror("malloc");
        free(series);
        pthread_exit(NULL);
    }
    res->series = series;
    res->length = length;
    return (void*)res;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <positive integers>\n", argv[0]);
        return 1;
    }

    int N = argc - 1;
    pthread_t *threads = (pthread_t*)malloc(N * sizeof(pthread_t));
    if (threads == NULL) {
        perror("malloc");
        return 1;
    }

    // Create threads for each command-line argument
    for (int i = 0; i < N; i++) {
        int num = atoi(argv[i + 1]);
        if (num <= 0) {
            fprintf(stderr, "Invalid positive integer: %s\n", argv[i + 1]);
            // Free resources and exit
            free(threads);
            return 1;
        }
        if (pthread_create(&threads[i], NULL, fibonacciGenerator, (void*)(intptr_t)num) != 0) {
            perror("pthread_create");
            free(threads);
            return 1;
        }
    }

    // Wait for each thread, collect result, and print
    for (int i = 0; i < N; i++) {
        void *result;
        if (pthread_join(threads[i], &result) != 0) {
            perror("pthread_join");
            free(threads);
            return 1;
        }
        struct FibResult *res = (struct FibResult*)result;
        printf("Thread %d: ", i);
        for (int j = 0; j < res->length; j++) {
            printf("%d", res->series[j]);
            if (j < res->length - 1) printf(", ");
        }
        printf("\n");
        // Free allocated memory
        free(res->series);
        free(res);
    }

    free(threads);
    return 0;
}