#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <ctype.h>

#define N 3
#define stringMaxLength 50

int main()
{
    char **shared_ptrs = (char **)mmap(NULL, sizeof(char *) * N,
                                       PROT_READ | PROT_WRITE,
                                       MAP_SHARED | MAP_ANONYMOUS,
                                       -1, 0);

    for (int i = 0; i < N; i++)
    {
        shared_ptrs[i] = (char *)mmap(NULL, stringMaxLength,
                                      PROT_READ | PROT_WRITE,
                                      MAP_SHARED | MAP_ANONYMOUS,
                                      -1, 0);
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    { // Child process
        printf("From child:\n");
        for (int i = 0; i < N; i++)
        {
            printf("Enter String %d: ", i + 1);
            fgets(shared_ptrs[i], stringMaxLength, stdin);
            // Remove trailing newline
            int len = strlen(shared_ptrs[i]);
            if (len > 0 && shared_ptrs[i][len - 1] == '\n')
                shared_ptrs[i][len - 1] = '\0';
        }

        exit(0);
    }
    else // Parent process
    {               
        wait(NULL); // Wait for child to finish

        // Convert each string to uppercase
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; shared_ptrs[i][j]; j++)
            {
                shared_ptrs[i][j] = toupper(shared_ptrs[i][j]);
            }
        }

        // Display results
        printf("From Parent:\n");
        for (int i = 0; i < N; i++)
        {
            printf("*** String %d ***\n", i + 1);
            printf("%s\n", shared_ptrs[i]);
            printf("Length = %ld\n\n", strlen(shared_ptrs[i]));
        }

        //
        for (int i = 0; i < N; i++)
        {
            munmap(shared_ptrs[i], stringMaxLength);
        }
        munmap(shared_ptrs, sizeof(char *) * N);

        return 0;
    }
}