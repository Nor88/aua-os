#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t printers;
pthread_mutex_t count_mutex;
int active_printers = 0;
int max_active_seen = 0;
int K = 3;
int N = 10;

void *print_job(void *arg) {
    int id = (int)(intptr_t)arg;

    sem_wait(&printers);

    pthread_mutex_lock(&count_mutex);
    active_printers++;
    if (active_printers > max_active_seen) {
        max_active_seen = active_printers;
    }
    printf("Thread %d is printing... (currently active: %d)\n", id, active_printers);
    pthread_mutex_unlock(&count_mutex);

    usleep(100000 + (rand() % 100000));

    pthread_mutex_lock(&count_mutex);
    active_printers--;
    printf("Thread %d finished printing. (currently active: %d)\n", id, active_printers);
    pthread_mutex_unlock(&count_mutex);

    sem_post(&printers);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc >= 2) K = atoi(argv[1]);
    if (argc >= 3) N = atoi(argv[2]);

    printf("Printers (K) = %d, Jobs (N) = %d\n", K, N);

    sem_init(&printers, 0, K);
    pthread_mutex_init(&count_mutex, NULL);

    pthread_t *threads = malloc(sizeof(pthread_t) * N);
    if (!threads) {
        perror("malloc");
        return 1;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, print_job, (void*)(intptr_t)i);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Maximum number of simultaneously active printers observed: %d\n",
           max_active_seen);

    sem_destroy(&printers);
    pthread_mutex_destroy(&count_mutex);
    free(threads);

    return 0;
}

