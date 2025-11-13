#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* calculate_square(void* arg) {
    int num = *(int*)arg;
    int square = num * num;
    printf("Square of %d is %d (Thread ID: %lu)\n", num, square, pthread_self());
    pthread_exit(NULL);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    pthread_t threads[size];

 
    for (int i = 0; i < size; i++) {
        if (pthread_create(&threads[i], NULL, calculate_square, &arr[i]) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    for (int i = 0; i < size; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished.\n");
    return 0;
}

