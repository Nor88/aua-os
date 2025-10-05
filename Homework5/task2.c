#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    int *arr;
    double sum = 0, average;

    printf("Enter the number of integers: ");
    scanf("%d", &n);

    arr = (int *)calloc(n, sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("\nInitial values in the array (from calloc):\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("\nEnter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nUpdated array values:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
        sum += arr[i];
    }
    printf("\n");

    average = sum / n;
    printf("\nThe average of the integers is: %.2f\n", average);

    free(arr);

    return 0;
}

