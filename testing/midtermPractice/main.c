
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



bool isPalindrome(char string[])
{
    int counter = strlen(string) - 1; 

    for (int i = 0; i < strlen(string)/2 ; i ++){
        if(string[i] != string[counter])
            return false;
        counter --; 
    }
    return true; 
}

int main(int argc, char **argv)
{

    int fd1[2];
    int fd2[2];
    char data[100];
    char *result;
    if (pipe(fd1) < 0 || pipe(fd2) < 0)
    {
        perror("Error");
        exit(0);
    }
    int pid = fork();
    if (pid < 0)
    {
        perror("Error Happen");
    }
    if (pid == 0)
    {
        /* code */
        close(fd1[0]);
        close(fd2[1]);

        //get data from user 
        fgets(data, sizeof(data), stdin);
        int len = strlen(data);

        //remove new line from input string 
        if (len > 0 && data[len - 1] == '\n')
            data[len - 1] = '\0';
        
        write(fd1[1],   data, strlen(data)+1);

        char result[100];

        read(fd2[0],result,sizeof(result));

        printf("%s\n",result);

    }
    if (pid > 0)
    {
        /* code */
                wait(0);

        close(fd1[1]);
        close(fd2[0]);

        read(fd1[0],data, sizeof(data));

        if(isPalindrome(data)){
            result = "Palindrome";
        } else {
            result = "Not Palindrome";
        }

        write(fd2[1] ,result, strlen(result) + 1 );
    }

    return 0;
}