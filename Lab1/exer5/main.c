#include <stdio.h>
#include <stdlib.h>

int multi(int a, int b, int c );

int main(int argc, char **argv)
{
    int i, j;
    scanf("%d%d", &i, &j);
    if (argc == 4)
    {
        printf("x = %d \ny = %d \nz = %d \ni = %d \nj = %d \n", atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), i, j);
        printf("Result of Multiply: %d \n", multi( atoi(argv[1]), atoi(argv[2]) , j));

    }
    else
    {
        printf("Error there should be 3 arguments in the command line inputted \n");
    }
    return 0;
}

int multi(int a, int b, int c )
{
    return a * b *c ;
}