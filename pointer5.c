#include <stdio.h>

int main() {
    char str[] = "Hello";

    char *ptr = str;

    printf("Printing the string using pointer:\n");
    while (*ptr != '\0') {
        printf("%c", *ptr);
        ptr++; // move the pointer to the next character
    }

    printf("\n");

    ptr = str;
    int count = 0;
    while (*ptr != '\0') {
        count++;
        ptr++;
    }

    printf("Number of characters: %d\n", count);

    return 0;
}

