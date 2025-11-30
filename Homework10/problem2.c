#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

long long balance = 0;

pthread_mutex_t balance_mutex;
pthread_spinlock_t balance_spin;

int use_mutex = 1;
int long_cs = 0;

int num_deposit_threads = 4;
int num_withdraw_threads = 4;
long long operations_per_thread = 500000LL;

void lock_balance() {
    if (use_mutex) {
        pthread_mutex_lock(&balance_mutex);
    } else {
        pthread_spin_lock(&balance_spin);
    }
}

void unlock_balance() {
    if (use_mutex) {
        pthread_mutex_unlock(&balance_mutex);
    } else {
        pthread_spin_unlock(&balance_spin);
    }
}

void *deposit_thread(void *arg) {
    for (long long i = 0; i < operations_per_thread; i++) {
        lock_balance();
        balance++;
        if (long_cs) {
            usleep(100);
        }
        unlock_balance();
    }
    return NULL;
}

void *withdraw_thread(void *arg) {
    for (long long i = 0; i < operations_per_thread; i++) {
        lock_balance();
        balance--;
        if (long_cs) {
            usleep(100);
        }
        unlock_balance();
    }
    return NULL;
}

double now_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
}

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        if (strcmp(argv[1], "mutex") == 0) use_mutex = 1;
        else if (strcmp(argv[1], "spin") == 0) use_mutex = 0;
    }

    if (argc >= 3) {
        if (strcmp(argv[2], "short") == 0) long_cs = 0;
        else if (strcmp(argv[2], "long") == 0) long_cs = 1;
    }

    if (argc >= 4) num_deposit_threads = atoi(argv[3]);
    if (argc >= 5) num_withdraw_threads = atoi(argv[4]);
    if (argc >= 6) operations_per_thread = atoll(argv[5]);

    printf("Mode: %s, critical section: %s\n",
           use_mutex ? "mutex" : "spin",
           long_cs ? "long" : "short");
    printf("Deposit threads: %d, Withdraw threads: %d, Ops per thread: %lld\n",
           num_deposit_threads, num_withdraw_threads, operations_per_thread);

    if (use_mutex) {
        pthread_mutex_init(&balance_mutex, NULL);
    } else {
        pthread_spin_init(&balance_spin, PTHREAD_PROCESS_PRIVATE);
    }

    int total_threads = num_deposit_threads + num_withdraw_threads;
    pthread_t *threads = malloc(sizeof(pthread_t) * total_threads);
    if (!threads) {
        perror("malloc");
        return 1;
    }

    int i;
    int idx = 0;

    double start = now_ms();

    for (i = 0; i < num_deposit_threads; i++) {
        pthread_create(&threads[idx++], NULL, deposit_thread, NULL);
    }
    for (i = 0; i < num_withdraw_threads; i++) {
        pthread_create(&threads[idx++], NULL, withdraw_thread, NULL);
    }

    for (i = 0; i < total_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    double end = now_ms();

    printf("Final balance: %lld (expected 0)\n", balance);
    printf("Elapsed time: %.2f ms\n", end - start);

    if (use_mutex) {
        pthread_mutex_destroy(&balance_mutex);
    } else {
        pthread_spin_destroy(&balance_spin);
    }

    free(threads);
    return 0;
}

