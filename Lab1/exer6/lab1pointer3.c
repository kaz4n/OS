#include <stdio.h>
void swap(int *a, int *b);

int main(int argc, char **argv)
{

    int a;
    int b;
    scanf("%d %d", &a, &b);
    printf("Before a and b are :%d %d \n", a, b);

    swap(&a, &b);
    printf("Now a and b are :%d %d \n", a, b);

    return 0;
}

void swap(int *a, int *b)
{
    int c = *b;
    *b = *a;
    *a = c;
}
