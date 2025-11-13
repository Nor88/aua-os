#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_function(void* arg){
	int thread_num = *(int*)arg;
	printf("Thread %d is running (ID: %lu\n", thread_num, pthread_self());
	pthread_exit(NULL);
}

int main(){
	pthread_t threads[3];
	int thread_args[3];
	int i;

	for(i = 0; i < 3; i++){
		thread_args[i] = i + 1;
		if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
        		 perror("Failed to create thread");
            		 exit(1);
        	}
	}

	for(i = 0; i < 3; i++){
		pthread_join(threads[i], NULL);
	}

	printf("All threads have finished.\n");
	return 0;
}
