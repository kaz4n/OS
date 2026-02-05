#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b);

int main(int argc, char **argv)
{

    if (argc == 3)
    {

        printf("%d \n", sum( atoi(argv[1]), atoi(argv[2])));
    }
    else
    {
        printf("Error there should be 2 arguments in the command line inputted \n");
    }
    return 0;
}

int sum(int a, int b)
{
    return a + b;
}