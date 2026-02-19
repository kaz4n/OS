#include <stdio.h>

int main() {
    char str[100];
    int num;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    printf("Enter an integer: ");
    scanf("%d", &num);

    printf("\nYou entered:\n");
    printf("String: %s", str);
    printf("Integer: %d\n", num);

    return 0;
}
