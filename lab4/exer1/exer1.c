#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int pipe_child_parent[2]; // child -> parent
    int pipe_parent_child[2]; // parent -> child
    pid_t pid;

    if (pipe(pipe_child_parent) == -1 || pipe(pipe_parent_child) == -1)
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
        char msg[100];
        int bytes_written, bytes_from_parent;

        close(pipe_child_parent[0]); // close read end
        close(pipe_parent_child[1]); // close write end

        printf("Enter a string\n");
        fgets(msg, sizeof(msg), stdin);

        // remove newline
        size_t len = strlen(msg);
        if (len > 0 && msg[len - 1] == '\n')
            msg[len - 1] = '\0';

            
        // send string to parent (include '\0')
        bytes_written = write(pipe_child_parent[1], msg, strlen(msg) + 1);

        printf("Child wrote %s\n", msg);
        printf("Child wrote %d bytes\n", bytes_written);

        // receive number of bytes the parent read
        read(pipe_parent_child[0], &bytes_from_parent, sizeof(bytes_from_parent));
        printf("Child: Length received from parent=%d\n", bytes_from_parent);
        printf("Child: Length transmitted=%d\n", bytes_written);

        if (bytes_written == bytes_from_parent)
            printf("Child: Message well received\n");
        else
            printf("Child: Message corrupted\n");

        close(pipe_child_parent[1]);
        close(pipe_parent_child[0]);
        exit(0);
    }
    else
    {
        char buffer[100];
        int bytes_read;
        int status;

        close(pipe_child_parent[1]); // close write end 
        close(pipe_parent_child[0]); // close read end 

        // read string from child
        bytes_read = read(pipe_child_parent[0], buffer, sizeof(buffer));

        printf("Parent read %s\n", buffer);
        printf("Parent read %d bytes\n", bytes_read);
        printf("Parent length received=%d\n", bytes_read);

        // send number of bytes back to child
        write(pipe_parent_child[1], &bytes_read, sizeof(bytes_read));

        close(pipe_child_parent[0]);
        close(pipe_parent_child[1]);

        wait(&status); // wait for child to finish
    }

    return 0;
}
