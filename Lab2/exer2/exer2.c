#include <stdio.h>

int main(){
    char input[10];
    int number; 
    fgets(input, sizeof(input), stdin);
    scanf("%d",&number);
    printf("User String Input: %s, User Integer Input: %d", input, number);
    
    return 0;
}