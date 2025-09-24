#include <stdio.h>
#include <stdlib.h>    // for exit()
#include <unistd.h>    // for fork(), getpid()
#include <sys/wait.h>  // for waitpid()

int main() {
    pid_t child1, child2;
    int status;

    child1 = fork();
    if (child1 == 0) {
        printf("Child 1 (PID = %d) running...\n", getpid());
        exit(5);   // child 1 exits with code 5
    }

    child2 = fork();
    if (child2 == 0) {
        printf("Child 2 (PID = %d) running...\n", getpid());
        exit(10);  // child 2 exits with code 10
    }

    printf("Parent (PID = %d) waiting for children...\n", getpid());

    waitpid(child1, &status, 0);
    if (WIFEXITED(status)) {
        printf("Parent: Child 1 exited normally with code %d\n", WEXITSTATUS(status));
    } else {
        printf("Parent: Child 1 did not exit normally\n");
    }

    waitpid(child2, &status, 0);
    if (WIFEXITED(status)) {
        printf("Parent: Child 2 exited normally with code %d\n", WEXITSTATUS(status));
    } else {
        printf("Parent: Child 2 did not exit normally\n");
    }

    return 0;
}

