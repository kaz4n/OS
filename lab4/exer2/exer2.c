#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd[2]; // fd[0] = read end, fd[1] = write end
    pid_t pid;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        int nums[10];

        close(fd[0]); // child doesn't read from pipe

        printf("Enter 10 numbers:\n");
        fflush(stdout);
        for (int i = 0; i < 10; i++)
        {
            printf("%d: ", i + 1);
            fflush(stdout);
            if (scanf("%d", &nums[i]) != 1) {
                fprintf(stderr, "Failed to read integer %d\n", i + 1);
                exit(EXIT_FAILURE);
            }
        }

        // send all 10 integers to parent
        if (write(fd[1], nums, sizeof(nums)) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(fd[1]);
        exit(0);
    }
    else
    {
        int nums[10];
        int sum = 0;

        close(fd[1]); // parent doesn't write to pipe

        if (read(fd[0], nums, sizeof(nums)) == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        close(fd[0]);

        for (int i = 0; i < 10; i++)
        {
            sum += nums[i];
        }

        printf("sum: %d\n", sum);

        // wait for child to finish
        wait(NULL); 
    }

    return 0;
}
