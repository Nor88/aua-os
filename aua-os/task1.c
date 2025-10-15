/*
 Variables of different types in memory are aligned according to their size and CPU requirements. The compiler may insert padding bytes so that each variable starts at an address that is a multiple of its type’s alignment (e.g., int on 4-byte boundaries, double on 8-byte boundaries). This ensures faster access by the CPU, but it can make the total size of a struct larger than the sum of its members. Smaller types like char may be placed with padding before or after them to maintain alignment.* */

#include <stdio.h>

int main() {
    int i;
    char c;
    double d;
    short s;

    // Print sizes of data types
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of i: %zu bytes\n", sizeof(i));
    printf("Size of char: %zu bytes\n", sizeof(char));
    printf("Size of c: %zu bytes\n", sizeof(c));
    printf("Size of double: %zu bytes\n", sizeof(double));
    printf("Size of d: %zu bytes\n", sizeof(d));
    printf("Size of short: %zu bytes\n", sizeof(short));
    printf("Size of s: %zu bytes\n", sizeof(s));

    // Print addresses of variables
    printf("Address of int i: %p\n", (void*)&i);
    printf("Address of char c: %p\n", (void*)&c);
    printf("Address of double d: %p\n", (void*)&d);
    printf("Address of short s: %p\n", (void*)&s);

    return 0;
}

