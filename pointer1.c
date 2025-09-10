
#include <stdio.h>

int main() {
    
    int num = 10;
    int *ptr = &num;

    printf("Address (num): %p\n", (void*)&num);
    printf("Address (pointer): %p\n", (void*)ptr);

    *ptr = 20;

    printf("New value after change: %d\n", num);
    return 0;
}

