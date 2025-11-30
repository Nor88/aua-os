#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long counter = 0;

pthread_mutex_t mtx;
pthread_spinlock_t sp;

int mode = 0;

void* worker(void *arg) {
    long long M = (long long)arg;
    for (long long i = 0; i < M; i++) {
        if (mode == 0) {
            counter++;
        } else if (mode == 1) {
            pthread_mutex_lock(&mtx);
            counter++;
            pthread_mutex_unlock(&mtx);
        } else if (mode == 2) {
            pthread_spin_lock(&sp);
            counter++;
            pthread_spin_unlock(&sp);
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int N = 4;
    long long M = 1000000;

    if (argc > 1) mode = atoi(argv[1]);
    if (argc > 2) N = atoi(argv[2]);
    if (argc > 3) M = atoll(argv[3]);

    if (mode == 1)
        pthread_mutex_init(&mtx, NULL);
    else if (mode == 2)
        pthread_spin_init(&sp, PTHREAD_PROCESS_PRIVATE);

    pthread_t threads[N];

    for (int i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, worker, (void*)M);

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    long long expected = (long long)N * M;

    printf("Mode: %d\n", mode);
    printf("Expected: %lld\n", expected);
    printf("Actual:   %lld\n", counter);

    if (mode == 1)
        pthread_mutex_destroy(&mtx);
    else if (mode == 2)
        pthread_spin_destroy(&sp);

    return 0;
}

