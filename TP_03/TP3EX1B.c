#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>

#define SIZE (int)1e8

// Thread version / Non-thread version in TP3EX1.c

int tab[SIZE];
int min = INT_MAX;
int max = INT_MIN;
pthread_mutex_t mutex;

void* find_min_max(void* arg) {
    int* range = (int*) arg;
    int thread_min = INT_MAX;
    int thread_max = INT_MIN;

    for (int i = range[0]; i < range[1]; i++) {
        if (tab[i] < thread_min) {
            thread_min = tab[i];
        }
        if (tab[i] > thread_max) {
            thread_max = tab[i];
        }
    }

    pthread_mutex_lock(&mutex);
    if (thread_min < min) {
        min = thread_min;
    }
    if (thread_max > max) {
        max = thread_max;
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}
void initialize_array() {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        tab[i] = rand();
    }
}

int main() {
    struct timeval start, end;

    initialize_array();

    int num_threads = 4;
    int range = SIZE / num_threads;
    pthread_t threads[num_threads];
    pthread_mutex_init(&mutex, NULL);

    gettimeofday(&start, NULL);
    for (int i = 0; i < num_threads; i++) {
        int start = i * range;
        int end = (i + 1) * range;
        int* thread_range = (int*) malloc(sizeof(int) * 2);
        thread_range[0] = start;
        thread_range[1] = end;
        pthread_create(&threads[i], NULL, find_min_max, (void*) thread_range);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end, NULL);

    // Affichage des résultats
    printf("Minimum: %d\n", min);
    printf("Maximum: %d\n", max);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("Time taken: %f seconds\n", time_taken);
    pthread_mutex_destroy(&mutex);

    return 0;
}
