#include <stdio.h>

int main() {
 
    int arr[5] = {0, 1, 2, 3, 4};

    int *ptr = arr;

    printf("Original array(pointer):\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");

    for (int i = 0; i < 5; i++) {
        *(ptr + i) += 12; 
    }

    printf("Modified array(pointer):\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");

    printf("Modified array(array name):\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

