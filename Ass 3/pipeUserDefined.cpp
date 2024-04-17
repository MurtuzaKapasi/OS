#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;

int main()
{
    int pipe1[2], pipe2[2];
    int status1, status2;
    int pid = 0;
    int maxLen = 20;
    char readmessage[maxLen];
    char pipe1writemessage[maxLen];
    char pipe2writemessage[maxLen];
    int n;

    cout << "Enter number of messages: ";
    cin >> n;
    cin.ignore();

    status1 = pipe(pipe1);
    status2 = pipe(pipe2);
    if (status1 == -1 || status2 == -1)
        cout << "error creating pipe";

    pid = fork();
    if (pid != 0)
    { // parent proces
        close(pipe1[0]);
        close(pipe2[1]);
        for (int i = 0; i < n; i++)
        {
            cout << "Enter message" << i + 1 << " from parent:";
            cin.getline(pipe1writemessage, maxLen);

            cout << "In parent: Writing to pipe 1 -> :" << pipe1writemessage << endl;
            write(pipe1[1], pipe1writemessage, strlen(pipe1writemessage) + 1);

            read(pipe2[0], readmessage, sizeof(readmessage));
            cout << "In parent - Reading child message ->: " << readmessage << endl;
        }
    }
    else
    { // child process

        close(pipe1[1]);
        close(pipe2[0]);
        for (int i = 0; i < n; i++)
        {
            read(pipe1[0], readmessage, sizeof(readmessage));
            cout << "In Child: reading message from parent ->: " << readmessage << endl;
            cout << "Enter Child's messaage: " << endl;
            cin.getline(pipe2writemessage, maxLen);

            cout << "Writing in child : " << pipe2writemessage << endl;
            write(pipe2[1], pipe2writemessage, strlen(pipe2writemessage) + 1);
        }
    }
    return 0;
}