#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_STUDENTS 100

typedef struct {
    int count;
    int grades[MAX_STUDENTS];
} shared_data;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Need to put his name");
        exit(0);
    }

    // Create shared memory for the structure
    int size = sizeof(shared_data);
    shared_data *shm = (shared_data *)mmap(NULL, size,
                                           PROT_READ | PROT_WRITE,
                                           MAP_SHARED | MAP_ANONYMOUS,
                                           -1, 0);
    if (shm == MAP_FAILED) {
        printf("error while making mmap");
        exit(0);
    }

    int pid = fork();
    if (pid < 0) {
        printf("error while fork");
        munmap(shm, size); //free memory
        exit(0);
    }

    if (pid == 0) {  // Child process
        int n;
        printf("Enter the number of students: ");
        scanf("%d", &n);
        getchar();  
        if (n <= 0 || n > MAX_STUDENTS) {
            //above maximum amout of student
            printf( "Invalid number of students (max %d)\n", MAX_STUDENTS);
            exit(0);
        }

        shm->count = n;
        printf("Child: Enter %d student values (e.g., IDs or scores):\n", n);
        for (int i = 0; i < n; i++) {
            printf("Student %d value: ", i + 1);
            scanf("%d", &shm->grades[i]);
        }
        printf("Child: Data written to shared memory.\n");

        munmap(shm, size); //free memory
        exit(0);
    }
    else {  // Parent process
        wait(NULL);  // Wait for child to finish

        // Open the output file
        FILE *file = fopen(argv[1], "w");
        if (file == NULL) {
            perror("fopen");
            munmap(shm, size);
            exit(EXIT_FAILURE);
        }

        printf("Parent: Writing student data to file '%s'...\n", argv[1]);
        for (int i = 0; i < shm->count; i++) {
            fprintf(file, "Student %d: %d\n", i + 1, shm->grades[i]);
        }
        fclose(file);
        printf("Parent: Data written successfully to '%s'.\n", argv[1]);

        
        if (munmap(shm, size) == -1) {
            perror("munmap");
        }
    }

    return 0;
}