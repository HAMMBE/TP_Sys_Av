#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t ps_pid, grep_pid;

    ps_pid = fork();
    if (ps_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (ps_pid == 0) {
        // ps

        // Ferme l'entrée du tube
        close(pipefd[0]);

        // Connecte la sortie de ps au tube
        dup2(pipefd[1], 1);

        // Exécute ps avec les options eaux
        execlp("ps", "ps", "eaux", NULL);

        perror("execlp ps");
        exit(EXIT_FAILURE);
    }

    grep_pid = fork();
    if (grep_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (grep_pid == 0) {
        close(pipefd[1]);

        dup2(pipefd[0], 0);
        int fd = open("/dev/null", O_WRONLY);
        dup2(fd,1);

        execlp("grep", "grep", "^root ", NULL);

        perror("execlp grep");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    int status;
    if (waitpid(grep_pid, &status, 0) == -1) {
        perror("waitpid grep");
        exit(EXIT_FAILURE);
    }

    if (WEXITSTATUS(status) == 0) {
        //root est connecté
        const char * message = "root est connecté\n";
        write(1, message, 18);
    }
    return 0;
}
