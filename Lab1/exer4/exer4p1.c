#include <stdio.h>

int main(int argc, char **argv) {
    
    int n;
    printf("input your desired max: ");
    scanf("%d",&n);

    int a = 1;
    while (a<=n){
    if(a%2 == 0 )
        printf("%d \n", a);
    a++;
    }
    
    return 0;
}
