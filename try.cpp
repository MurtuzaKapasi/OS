#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace  std;
void processFork(){
    pid_t pid = fork();
    if(pid == 0){
        //child process
        cout<<"Im child process "<< getpid()<<endl;
        execl("/bin/echo" , "echo" , "Hello from child",nullptr);

    }
    else if(pid > 0){
        //parent process
        cout<<"This is parent process "<<getpid()<<endl;
        int status;
        wait(&status);
        cout<<"Child is reaped "<<status<<endl;
         if (WIFEXITED(status)) {
            cout << "The process ended with exit(" << WEXITSTATUS(status) << ")." << endl;
        }
    }
    exit(0);
}
int main(){
    processFork();
    return 0;
}


