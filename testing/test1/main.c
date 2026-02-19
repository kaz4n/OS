#include <stdio.h>
#include <string.h>

typedef struct people {

    char *str;
} People;
int main(int argc, char* [] argv){
    
    // char* str = "Hello";
    // char str1[12] = {'s', '2'};
    // char charect = '2';
    // printf("%s , %c ", str , charect);

    // struct people pp;
    // pp.str =  "Hello";
    // printf("%s  ", pp.str);

if (argc < 2) {
    fprintf(stderr, "Usage: %s <number>\n", argv[0]);
    return 1;
}
    int a = atoi(argv[1]);
    printf("%d", a);
    return 0;
}