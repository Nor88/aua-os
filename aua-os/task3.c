/*
 * Packing changes how the compiler aligns struct members in memory. Normally, the compiler adds padding bytes so each member is aligned for fast CPU access. When packing is applied (e.g., #pragma pack(1)), padding is reduced or removed, so members are stored tightly together. This makes the struct smaller in size, but access may be slower because members may not be aligned to the CPU’s preferred boundaries.*/

#include <stdio.h>

struct Task3 {
    int a;
    int b;
    int c;
};

int main() {
    struct Task3 s;

    // Print size of the struct
    printf("Size of s: %zu byte\n", sizeof(s));

    // Print addresses of members
    printf("Address of a: %p\n", (void*)&s.a);
    printf("Address of b: %p\n", (void*)&s.b);
    printf("Address of c: %p\n", (void*)&s.c);

    return 0;
}

