#include <stdio.h>

int main()
{
    printf("Main Process PID =%d PPID=%d\n", getpid(), getppid());

    int pid = fork();
    if (pid < 0)
    {
        perror("Error forking a child");
        int exitCode = exit(0);
        execlp("/date", "date", "" + % Y - % m - % d % H : % M : % S "", (char *)0);
    }
    else if (pid = 0)
    {
        printf("Child Process PID =%d PPID=%d\n", pid, getpid());
    }
    else
    {
        wait(NULL);
        printf("Child Process PID =%d PPID=%d\n", exitCode);
        printf("Parent Process PID=%d, child PID=%d, PPID=%d\n", getpid(), pid, getppid());
        if (exitCode == 0)
            printf("Child succeeded!\n");
        else
            printf("Child Failed (status=%d)\n", exitCode);
    }
    return 1;
}