#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int status;
    printf("Main Process PID =%d PPID=%d\n", getpid(), getppid());
    int pid = fork();
    if (pid < 0)
    {
        perror("Error forking a child");
        exit(0);
    }
    else if (pid = 0)
    {
        printf("Child Process PID =%d PPID=%d\n", pid , getpid());
    }
    else
    {
        wait(NULL);
        printf("Parent Process PID=%d, child PID=%d, PPID=%d\n", getpid(), pid, getppid());
        if(WIFEXITED(status)){
            int exitCode = WEXITSTATUS(status);
        printf("Child exit code=%d\n", exitCode);
            if (exitCode == 0)
                printf("Child succeeded!\n");
            else
                printf("Child Failed (status=%d)\n", exitCode);
        } else {
            printf("Child did not terminate normally\n");
        }
    return 1;
}
}