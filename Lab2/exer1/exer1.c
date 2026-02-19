#include <stdio.h>

int main()
{
    char input[10];
    printf("Enter a string: ");

    fgets(input, sizeof(input), stdin);
    printf("I am kidding you don't have a quiz for this time :P");
    return 0;
}