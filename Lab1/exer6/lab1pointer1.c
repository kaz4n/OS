#include <stdio.h>

int main() {
    int a = 1;
    int b = 2;

    int *e = &b;

    int *f;
    f = &b;

    printf(
        "a = %d\n b = %d\n e = %p\n *e = %d\n &e = %p\n &b = %p\n f = %p\n *f = %d\n &f = %p\n", 
        a, b, (void*)e, *e, (void*)&e, (void*)&b, (void*)f, *f, (void*)&f);
    
    return 0;
}
