#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// Non-Thread Version / Thread Version in TP3EX1B.c

#define SIZE (int)1e8
int tab[SIZE];

int main() {
    struct timeval start, end;
    int min, max;

    // Initialisation du tableau avec des valeurs aléatoires
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        tab[i] = rand();
    }

    // Recherche du minimum et du maximum
    gettimeofday(&start, NULL);
    min = tab[0];
    max = tab[0];
    for (int i = 1; i < SIZE; i++) {
        if (tab[i] < min) {
            min = tab[i];
        }
        if (tab[i] > max) {
            max = tab[i];
        }
    }
    gettimeofday(&end, NULL);

    // Affichage des résultats
    printf("Minimum: %d\n", min);
    printf("Maximum: %d\n", max);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("Time taken: %f seconds\n", time_taken);
    return 0;
}