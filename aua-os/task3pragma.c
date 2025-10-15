#include <stdio.h>


#pragma pack(1)
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

