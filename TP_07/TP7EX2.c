#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not enough argument \n", argv[0]);
        return 1;
    }

    int memory_size = atoi(argv[1]);
    int block_size = 1024 * 1024; // 1 MB
    int blocks = memory_size / block_size;

    char *array[blocks];
    for (int i = 0; i < blocks; i++) {
        array[i] = malloc(block_size);
        if (array[i] == NULL) {
            printf("Could not allocate memory\n");
            break;
        }
        memset(array[i], 0, block_size);
    }

    while (1) {
        sleep(1);
    }

    return 0;
}
