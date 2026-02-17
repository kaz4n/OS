#include <stdio.h>
#include <string.h>

int main(){
    char hello[6] = {'h','e','l','l','o','\0'};
    for(int i = 0; i<strlen(hello); i++){
        for (int chr = i; chr<strlen(hello); chr++)
        {
            printf("%c", hello[chr]);

        }

        printf("\n");
    }
    return 0;
}