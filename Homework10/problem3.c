#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 8

int buffer[BUFFER_SIZE];
int in_pos  = 0;
int out_pos = 0;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;

int P = 3;
int C = 2;
int ITEMS_PER_PRODUCER = 10;

int total_items;
int consumed_count = 0;

void *producer(void *arg) {
    int id = (int)(intptr_t)arg;
    for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
        int item = id * 1000 + i;
        sem_wait(&empty_slots);
        pthread_mutex_lock(&buffer_mutex);
        buffer[in_pos] = item;
        in_pos = (in_pos + 1) % BUFFER_SIZE;
        printf("Producer %d produced %d\n", id, item);
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full_slots);
        usleep(5000);
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = (int)(intptr_t)arg;
    while (1) {
        sem_wait(&full_slots);
        pthread_mutex_lock(&buffer_mutex);
        if (consumed_count >= total_items) {
            pthread_mutex_unlock(&buffer_mutex);
            sem_post(&full_slots);
            break;
        }
        int item = buffer[out_pos];
        out_pos = (out_pos + 1) % BUFFER_SIZE;
        consumed_count++;
        printf("Consumer %d consumed %d (total consumed = %d)\n",
               id, item, consumed_count);
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_slots);
        if (consumed_count >= total_items) {
            break;
        }
        usleep(7000);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc >= 2) P = atoi(argv[1]);
    if (argc >= 3) C = atoi(argv[2]);
    if (argc >= 4) ITEMS_PER_PRODUCER = atoi(argv[3]);

    total_items = P * ITEMS_PER_PRODUCER;

    printf("Producers: %d, Consumers: %d, Items per producer: %d, Total: %d\n",
           P, C, ITEMS_PER_PRODUCER, total_items);

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    pthread_mutex_init(&buffer_mutex, NULL);

    pthread_t *producers = malloc(sizeof(pthread_t) * P);
    pthread_t *consumers = malloc(sizeof(pthread_t) * C);

    if (!producers || !consumers) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < P; i++) {
        pthread_create(&producers[i], NULL, producer, (void*)(intptr_t)i);
    }
    for (int i = 0; i < C; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void*)(intptr_t)i);
    }

    for (int i = 0; i < P; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < C; i++) {
        pthread_join(consumers[i], NULL);
    }

    printf("All items produced and consumed. Final consumed_count = %d\n",
           consumed_count);

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&buffer_mutex);

    free(producers);
    free(consumers);

    return 0;
}

