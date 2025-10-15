/*

Rearranging the fields in a struct can **increase or decrease its size** because of **memory alignment and padding**. The compiler inserts extra bytes (padding) so each field starts at an address suitable for the CPU. By grouping larger fields first and smaller fields together, you can **reduce padding** and make the struct **smaller**. Conversely, a poor order can increase the struct size.
.
 * */


#include <stdio.h>

struct Assignment {
    char c;
    int b;
    double a;
};

int main() {
    struct Assignment assign;

    // Print size of the struct
    printf("Size of Assignment: %zu byte\n", sizeof(assign));

    // Print addresses of members
    printf("Address of a: %p\n", (void*)&assign.a);
    printf("Address of b: %p\n", (void*)&assign.b);
    printf("Address of c: %p\n", (void*)&assign.c);

    return 0;
}

