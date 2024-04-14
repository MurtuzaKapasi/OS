#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void performSystemCalls() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("It is the child process and pid is %d\n", getpid());

        // execl("/bin/ls", "ls", "-l", "/home/ubuntu/", (char *) 0);
        execl("/bin/echo", "echo", "Hello from the child process!", (char *)0);
        perror("In exec(): ");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        printf("It is the parent process and pid is %d\n", getpid());

        int status;
        wait(&status);
        printf("Child is reaped %d\n" , status);

        if (WIFEXITED(status)) {
            printf("The process ended with exit(%d).\n", WEXITSTATUS(status));
        }

        if (WIFSIGNALED(status)) {
            printf("The process ended with kill -%d.\n", WTERMSIG(status));
        }
    } else {
        printf("Error while forking\n");
        exit(EXIT_FAILURE);
    }

    exit(0);
}

int main() {
    performSystemCalls();
    return 0;
}
