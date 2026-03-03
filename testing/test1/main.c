#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE_ARRAY 8



int main() {


    if (fork() && fork() )
    {
        fork();
    }
    
    int pid = fork();
    if (pid == 0 )
    {
        int pid2 = fork();
        if(pid2 == 0){
            execvp("ls",args);
        }
        else if (pid2> 0)
        {
            WAIT(NULL);
        }
    
    WAIT(NULL);
    printf("Something");
    }
    
    // for (size_t i = 0; i < 2; i++)
    // {
    //     fork();
    // }

    //  if (fork() == 0  )
    // {
    //     fork();
    // }
    // int buffer[8] = {0,1,2,3,4,5,6,7};
    // for(int i = 0; i < SIZE_ARRAY; i++){
    //     printf("%d", (buffer[i]% SIZE_ARRAY));
    // } 

    return 0;
}