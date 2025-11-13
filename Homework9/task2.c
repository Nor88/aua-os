#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 8

int arr[SIZE] = {2, 4, 6, 8, 10, 12, 14, 16};

typedef struct{
	int start;
	int end;
}
ThreadData;

void* partial_sum(void* arg){
		ThreadData* data = (ThreadData*)arg;
		int sum = 0;
		for(int i = data->start; i < data->end; i++){
			sum += arr[i];
		}

		printf("Thread handling indices %d to %d: partial sum = %d\n", data->start, data->end - 1, sum);
		pthread_exit(NULL);
}

int main(){
	pthread_t threads[2];
    ThreadData thread_data[2];

    int mid = SIZE / 2;

    // Assign first half to thread 1
    thread_data[0].start = 0;
    thread_data[0].end = mid;

    // Assign second half to thread 2
    thread_data[1].start = mid;
    thread_data[1].end = SIZE;

    // Create threads
    pthread_create(&threads[0], NULL, partial_sum, &thread_data[0]);
    pthread_create(&threads[1], NULL, partial_sum, &thread_data[1]);

    // Wait for threads to finish
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    printf("Both threads have completed their partial sums.\n");
    return 0;
}
