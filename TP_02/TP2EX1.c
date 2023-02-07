#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0) {
        printf("I am the child process with pid %d and my parent is %d\n", getpid(), getppid());
        exit(0);
    } else {
        printf("I am the parent process with pid %d and my children is %d\n", getpid(), pid);
        waitpid(pid, &status, 0);
        //show exit code of children process
        printf("Exit code of children process is %d\n", status);
    }
    return 0;
}