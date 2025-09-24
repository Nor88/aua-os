#include <stdio.h>
#include <unistd.h>   // fork(), getpid()
#include <stdlib.h>   // exit()

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: PID = %d\n", getpid());
        exit(0);   // child ends immediately
    } 
    else {
        // Parent process does not call wait()
        printf("Parent: PID = %d (not waiting for child)\n", getpid());
        // Keep parent alive so we can see the zombie
        sleep(30);  
    }

    return 0;
}

