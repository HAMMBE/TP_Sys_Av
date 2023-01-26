#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int temp_file_desc;
    char temp_file_path[] = "/tmp/proc-exercise";

    if (argc != 2) {
        printf("Erreur : le nombre de paramètres est incorrect.\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("Erreur lors de la création du fils");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Fils
        printf("PID du fils : %d\n", getpid());

        // Ferme le descripteur 1 (STDOU)
        close(1);
        //close(2);

        // Ouvre le fichier temporaire en création et écriture
        temp_file_desc = mkstemp(temp_file_path);

        // Affiche le numéro du descripteur du fichier ouvert
        printf("Descripteur du fichier temporaire : %d\n", temp_file_desc);

        // Remplace le descripteur 1 avec le descripteur du fichier temporaire
        dup2(temp_file_desc, 1);

        // Exécute le programme passé en argument
        execl(argv[1], argv[1], NULL);

        perror("Erreur lors de l'exécution du programme");
        exit(EXIT_FAILURE);
    } else {
        // Père
        printf("PID du père : %d\n", getpid());

        // Attend la fin du fils
        wait(NULL);

        printf("That's All Folks !\n");
    }

    return 0;
}
