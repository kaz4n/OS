#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// function for beginning of sentence
void *print_beginning(void *arg) {
    printf("How");
    return NULL;
}

//  function for middle of sentence
void *print_middle(void *arg) {
    printf(" are");
    return NULL;
}

// function for end of sentence
void *print_end(void *arg) {
    printf(" you?\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    // Create 3 threads with no synchronization
    pthread_create(&thread1, NULL, print_beginning, NULL);
    pthread_create(&thread2, NULL, print_middle, NULL);
    pthread_create(&thread3, NULL, print_end, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}