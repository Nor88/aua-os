#include <stdio.h>
#include <unistd.h>     // fork(), getpid()
#include <stdlib.h>     // exit()
#include <sys/wait.h>   // wait()

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: PID = %d\n", getpid());
        exit(0);   // child ends
    } 
    else {
        // Parent waits for child
        int status;
        wait(&status);
        printf("Parent: PID = %d collected child, no zombie created.\n", getpid());
        sleep(5);  // parent lives a bit longer
    }

    return 0;
}

