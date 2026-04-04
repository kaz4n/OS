#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_begin, sem_middle, sem_end;

// Thread function for beginning of sentence
void *print_beginning(void *arg) {
    sem_wait(&sem_begin);          // Wait for permission
    printf("How");
    sem_post(&sem_middle);         // Signal middle thread
    return NULL;
}

// Thread function for middle of sentence
void *print_middle(void *arg) {
    sem_wait(&sem_middle);         // Wait for beginning to finish
    printf(" are");
    sem_post(&sem_end);            // Signal end thread
    return NULL;
}

// Thread function for end of sentence
void *print_end(void *arg) {
    sem_wait(&sem_end);            // Wait for middle to finish
    printf(" you?\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    // Initialize semaphores: begin = 1 (ready), others = 0 (blocked)
    sem_init(&sem_begin, 0, 1);
    sem_init(&sem_middle, 0, 0);
    sem_init(&sem_end, 0, 0);

    // Create threads
    pthread_create(&thread1, NULL, print_beginning, NULL);
    pthread_create(&thread2, NULL, print_middle, NULL);
    pthread_create(&thread3, NULL, print_end, NULL);

    // Wait for all threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Destroy semaphores
    sem_destroy(&sem_begin);
    sem_destroy(&sem_middle);
    sem_destroy(&sem_end);

    return 0;
}