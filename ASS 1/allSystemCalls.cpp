#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

void performSystemCalls() {
    pid_t pid = fork();
    pid_t pid2 = fork();

    if (pid == 0 || pid2==0) {
        cout << "It is the child process and pid is " << getpid() << endl;

        // Using C++ string literals and cout for output
        execl("/bin/echo", "echo", "Hello from the child process!", nullptr);
        perror("In exec(): ");
        exit(EXIT_FAILURE);
    } else if (pid > 0 || pid2 > 0) {
        cout << "It is the parent process and pid is " << getpid() << endl;

        int status;
        wait(&status);
        cout << "Child is reaped " << status << endl;

        if (WIFEXITED(status)) {
            cout << "The process ended with exit(" << WEXITSTATUS(status) << ")." << endl;
        }

        if (WIFSIGNALED(status)) {
            cout << "The process ended with kill -" << WTERMSIG(status) << "." << endl;
        }
    } 
    exit(0);
}

int main() {
    performSystemCalls();
    return 0;
}
