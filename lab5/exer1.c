#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
 

        close(fd[0]); 

        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp("cat", "cat", "file.txt", NULL);

        perror("execlp cat");
        exit(1);
    }
    else {
    
        close(fd[1]); 

        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        execlp("grep", "grep", "word", NULL);

        perror("execlp grep");
        exit(1);
    }

    return 0;
}
