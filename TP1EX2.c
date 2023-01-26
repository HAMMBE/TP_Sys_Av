#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;
    int i;
    char c;
    struct stat st;

    if (argc != 2) {
        printf("Erreur : le nombre de paramètres est incorrect.\n");
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    if (fstat(fd, &st) == -1) {
        perror("Erreur lors de la récupération des informations du fichier");
        exit(EXIT_FAILURE);
    }

    for (i = st.st_size - 1; i >= 0; i--) {
        lseek(fd, i, SEEK_SET);
        read(fd, &c, 1);
        printf("%c", c);
    }

    printf("\n");

    close(fd);

    return 0;
}
