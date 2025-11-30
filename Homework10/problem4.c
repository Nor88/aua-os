#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semA, semB, semC;
pthread_mutex_t print_mutex;
int N = 5;

void *thread_A(void *arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semA);
        pthread_mutex_lock(&print_mutex);
        printf("Thread A: A %d\n", i);
        pthread_mutex_unlock(&print_mutex);
        sem_post(&semB);
    }
    return NULL;
}

void *thread_B(void *arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semB);
        pthread_mutex_lock(&print_mutex);
        printf("Thread B: B %d\n", i);
        pthread_mutex_unlock(&print_mutex);
        sem_post(&semC);
    }
    return NULL;
}

void *thread_C(void *arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semC);
        pthread_mutex_lock(&print_mutex);
        printf("Thread C: C %d\n", i);
        pthread_mutex_unlock(&print_mutex);
        sem_post(&semA);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc >= 2) N = atoi(argv[1]);

    sem_init(&semA, 0, 1);
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);
    pthread_mutex_init(&print_mutex, NULL);

    pthread_t ta, tb, tc;
    pthread_create(&ta, NULL, thread_A, NULL);
    pthread_create(&tb, NULL, thread_B, NULL);
    pthread_create(&tc, NULL, thread_C, NULL);

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    pthread_join(tc, NULL);

    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);
    pthread_mutex_destroy(&print_mutex);

    return 0;
}

