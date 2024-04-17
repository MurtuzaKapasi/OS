#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

void performSystemCalls() {
    pid_t pid1 = fork();
    pid_t pid2 = -1; // Initialize pid2 to -1 to distinguish it from child process
    pid_t pid3 = -1; // Initialize pid3 to -1 to distinguish it from child process

    if (pid1 == 0) 
    {
        cout << "It is the first child process and pid is " << getpid() << endl;
        // Using C++ string literals and cout for output
        execl("/bin/echo", "echo", "Hello from the first child process!", nullptr);
        perror("In exec(): ");
        exit(EXIT_FAILURE);
    } else if (pid1 > 0) {
        // Inside the parent process
        pid2 = fork(); // Create second child process

        if (pid2 == 0) {
            cout << "It is the second child process and pid is " << getpid() << endl;

            // Using C++ string literals and cout for output
            execl("/bin/echo", "echo", "Hello from the second child process!", nullptr);
            perror("In exec(): ");
            exit(EXIT_FAILURE);
        } else if (pid2 > 0) {
            // Inside the parent process
            pid3 = fork(); // Create third child process

            if (pid3 == 0) {
                cout << "It is the third child process and pid is " << getpid() << endl;

                // Using C++ string literals and cout for output
                execl("/bin/echo", "echo", "Hello from the third child process!", nullptr);
                perror("In exec(): ");
                exit(EXIT_FAILURE);
            } else if (pid3 > 0) {
                // Inside the parent process
                cout << "It is the parent process and pid is " << getpid() << endl;

                // Wait for all child processes to terminate
                int status;
                waitpid(pid1, &status, 0);
                waitpid(pid2, &status, 0);
                waitpid(pid3, &status, 0);

                cout << "All child processes have terminated." << endl;
            } else {
                cerr << "Error while forking for third child" << endl;
                exit(EXIT_FAILURE);
            }
        } else {
            cerr << "Error while forking for second child" << endl;
            exit(EXIT_FAILURE);
        }
    } else {
        cerr << "Error while forking for first child" << endl;
        exit(EXIT_FAILURE);
    }

    exit(0);
}

int main() {
    performSystemCalls();
    return 0;
}
