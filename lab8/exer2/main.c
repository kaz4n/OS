#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

// Structure to hold the array of numbers and its size
struct Data {
    int *arr;
    int count;
};

// Thread function for average
void *average(void *arg) {
    struct Data *data = (struct Data*)arg;
    int sum = 0;
    for (int i = 0; i < data->count; i++) {
        sum += data->arr[i];
    }
    double avg = (double)sum / data->count;
    // Return a pointer to a dynamically allocated double
    double *result = (double*)malloc(sizeof(double));
    if (result == NULL) {
        perror("malloc");
        pthread_exit(NULL);
    }
    *result = avg;
    return (void*)result;
}

// Thread function for maximum
void *maximum(void *arg) {
    struct Data *data = (struct Data*)arg;
    int max = data->arr[0];
    for (int i = 1; i < data->count; i++) {
        if (data->arr[i] > max) max = data->arr[i];
    }
    return (void*)(intptr_t)max;
}

// Thread function for minimum
void *minimum(void *arg) {
    struct Data *data = (struct Data*)arg;
    int min = data->arr[0];
    for (int i = 1; i < data->count; i++) {
        if (data->arr[i] < min) min = data->arr[i];
    }
    return (void*)(intptr_t)min;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <list of integers>\n", argv[0]);
        return 1;
    }

    int count = argc - 1;
    int *numbers = (int*)malloc(count * sizeof(int));
    if (numbers == NULL) {
        perror("malloc");
        return 1;
    }

    // Parse command-line arguments
    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    struct Data data = { numbers, count };
    pthread_t threads[3];
    void *results[3];

    // Create threads
    if (pthread_create(&threads[0], NULL, average, (void*)&data) != 0) {
        perror("pthread_create (average)");
        free(numbers);
        return 1;
    }
    if (pthread_create(&threads[1], NULL, maximum, (void*)&data) != 0) {
        perror("pthread_create (maximum)");
        free(numbers);
        return 1;
    }
    if (pthread_create(&threads[2], NULL, minimum, (void*)&data) != 0) {
        perror("pthread_create (minimum)");
        free(numbers);
        return 1;
    }

    // Wait for threads and collect results
    if (pthread_join(threads[0], &results[0]) != 0) {
        perror("pthread_join (average)");
        free(numbers);
        return 1;
    }
    if (pthread_join(threads[1], &results[1]) != 0) {
        perror("pthread_join (maximum)");
        free(numbers);
        return 1;
    }
    if (pthread_join(threads[2], &results[2]) != 0) {
        perror("pthread_join (minimum)");
        free(numbers);
        return 1;
    }

    // Print results
    double avg = *(double*)results[0];
    int max = (int)(intptr_t)results[1];
    int min = (int)(intptr_t)results[2];

    // Since the example shows integer division, we cast to int
    printf("The average value is %d\n", (int)avg);
    printf("The minimum value is %d\n", min);
    printf("The maximum value is %d\n", max);

    // Free allocated memory
    free(results[0]);   // free the double allocated in average thread
    free(numbers);
    return 0;
}