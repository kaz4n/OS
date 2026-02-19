#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    printf("Main Process PID =%d PPID=%d\n", getpid(), getppid());
    int status;
    int pid = fork();
    // error happens in forking
    if (pid < 0)
    {
        perror("Error forking a child");
    }
    // child
    else if (pid == 0)
    {
        printf("Child Process PID =%d PPID=%d\n", getpid(), getppid());
        execlp("date", "date", (char *)NULL);
        perror("execlp failed");
        _exit(1);
    }
    // parent
    else
    {
        if (wait(&status) < 0)
        {
            perror("wait failed");
            exit(1);
        }
        printf("Parent Process PID=%d, child PID=%d, PPID=%d\n", getpid(), pid, getppid());
        // error happens
        if (WIFEXITED(status))
        {
            int exitCode = WEXITSTATUS(status);
            printf("Child exit code=%d\n", exitCode);
            if (exitCode == 0)
                printf("Child succeeded!\n");
            else
                printf("Child Failed (status=%d)\n", exitCode);
        }
        else
        {
            printf("Child did not terminate normally\n");
        }
        return 0;
    }
}