#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZEOFTHEBUFFER 20

typedef struct {
    int buffer[SIZEOFTHEBUFFER];
    int in;
    int out;
    int counter;
} shared_data;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Need 1 argument\n" );
        exit(1);
    }

    int mmap_size = atoi(argv[1]);

    // Create shared memory using mmap
    shared_data *data = mmap(NULL, mmap_size,
                             PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS,
                             -1, 0);

    if (data == MAP_FAILED) {
        printf("mmap failed, there's an error");
        exit(1);
    }

    // Initialize shared variables
    data->in = 0;
    data->out = 0;
    data->counter = 0;

    int pid = fork();

    if (pid < 0) {
        printf("fork failed,, theres an error");
        exit(1);
    }

    //parent which is the producer

    if (pid > 0) {

                printf("parent producer started.\n");

        for (int item = 1; item <= 20; item++) {

            // Wait if buffer full
            while (data->counter == SIZEOFTHEBUFFER) {
                printf("Code is hanging\n");
                usleep(100000);
            }
            // Produce item
            data->buffer[data->in] = item;
            printf("Producer produced: %d\n", item);

            data->in = (data->in + 1) % SIZEOFTHEBUFFER;
            data->counter++;

            sleep(1); 
        }

        wait(NULL);
        printf("parent cleaning up...\n");
        munmap(data, mmap_size);
        printf("parent done.\n");   
    }

    //Child which is the consumer
    else {
        printf("child consumer started.\n");
        int item;

        while (1) {

            // Wait if buffer empty
                while (data->counter == 0) {
                printf("Code is hanging\n");
                usleep(100000);
            }
            item = data->buffer[data->out];
            printf("Consumer consumed: %d\n", item);

            data->out = (data->out + 1) % SIZEOFTHEBUFFER;
            data->counter--;

            if (item == 20){
                break;
                            printf("child reached item number20. Exit\n");
    
            }

            sleep(1); 
        }

        exit(0);
    }

    // Cleanup
    munmap(data, mmap_size);

    return 0;
}