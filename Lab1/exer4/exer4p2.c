/*EXERCISE 3: Q2 from Lab1_Tutorial (slide#26)*/

#include <stdio.h>
#include <stdlib.h>

int find_max (int a, int b, int c) {
    if (a > b) {
        if (a > c) return a;
        else return c;
    }
    else if (b > c) {
        return b;
    }
    else {
        return c;
    }
}

int main (int argc, char **argv) {
    if (argc != 3) {
        printf ("You should only enter 2 numbers in the cmd line!\n");
    }
    else {
        int a, b, c;
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        printf("Enter 3rd num: ");
        scanf("%d", &c);
        printf("Maximum between %d, %d and %d is %d\n\n", a, b, c, find_max(a, b, c));
    }
    return 0;
}
