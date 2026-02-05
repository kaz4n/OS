#include <stdio.h>

int main(int argc, char **argv) {
    
    int a, b;
    scanf("%d",&a);
    scanf("%d",&b);

    int c = b; 
    b = a; 
    a = c; 
    
    printf("%d %d\n ", a, b);
    return 0;
}
