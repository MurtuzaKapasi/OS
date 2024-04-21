#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    int pipefds1[2], pipefds2[2];
    int returnstatus1, returnstatus2;
    int pid;
    int n;
    const int max_message_length = 20;
    char pipe1writemessage[max_message_length];
    char pipe2writemessage[max_message_length];
    char readmessage[max_message_length];

    cout << "Enter the number of messages to send: ";
    cin >> n;
    cin.ignore(); // ignore the newline character in the input buffer

    returnstatus1 = pipe(pipefds1);

    if (returnstatus1 == -1) {
        cerr << "Unable to create pipe 1" << endl;
        return 1;
    }

    returnstatus2 = pipe(pipefds2);

    if (returnstatus2 == -1) {
        cerr << "Unable to create pipe 2" << endl;
        return 1;
    }

    pid = fork();

    if (pid != 0) { // Parent process
        close(pipefds1[0]); // Close the unwanted pipe1 read side
        close(pipefds2[1]); // Close the unwanted pipe2 write side

        for (int i = 0; i < n; ++i) {
            cout << "In Parent: Enter message " << i + 1 << " for pipe 1: ";
            cin.getline(pipe1writemessage, max_message_length);

            cout << "In Parent: Writing to pipe 1 – Message is : " << pipe1writemessage << endl;
            write(pipefds1[1], pipe1writemessage, strlen(pipe1writemessage) + 1);

            read(pipefds2[0], readmessage, sizeof(readmessage));
            cout << "In Parent: Reading from pipe 2 – Message is : " << readmessage << endl;
        }
    } else { // Child process
        close(pipefds1[1]); // Close the unwanted pipe1 write side
        close(pipefds2[0]); // Close the unwanted pipe2 read side

        for (int i = 0; i < n; ++i) {
            read(pipefds1[0], readmessage, sizeof(readmessage));
            cout << "In Child: Reading from pipe 1 – Message is : " << readmessage << endl;

            cout << "In Child: Enter message " << i + 1 << " for pipe 2: ";
            cin.getline(pipe2writemessage, max_message_length);

            cout << "In Child: Writing to pipe 2 – Message is : " << pipe2writemessage << endl;
            write(pipefds2[1], pipe2writemessage, strlen(pipe2writemessage) + 1);
        }
    }

    return 0;
}

