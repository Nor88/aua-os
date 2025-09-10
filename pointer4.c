#include <stdio.h>

int main() {
    int num = 299;
    int *ptr = &num;
    int **pptr = &ptr;

    printf("Value directly: %d\n", num);
    printf("Value using single pointer (*ptr): %d\n", *ptr);
    printf("Value using double pointer (**pptr): %d\n", **pptr);
    printf("\nAddress of num: %p\n", (void*)&num);
    printf("Address stored in ptr(address of num): %p\n", (void*)ptr);
    printf("Address stored in pptr(address of ptr): %p\n", (void*)pptr);
    return 0;
}
