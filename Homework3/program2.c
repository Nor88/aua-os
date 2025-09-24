#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child1, child2;
    int status;

    // First child
    child1 = fork();
    if (child1 == 0) {
        printf("Child 1: PID = %d\n", getpid());
        return 10;   // child 1 ends
    }

    // Second child
    child2 = fork();
    if (child2 == 0) {
        printf("Child 2: PID = %d\n", getpid());
        return 20;   // child 2 ends
    }

    printf("Parent: PID = %d\n", getpid());

    pid_t finished = wait(&status);
    if (finished > 0 && WIFEXITED(status)) {
        printf("Parent: Child with PID %d finished, exit code = %d\n",
               finished, WEXITSTATUS(status));
    }

    pid_t specific = waitpid(child2, &status, 0);
    if (specific > 0 && WIFEXITED(status)) {
        printf("Parent: Child 2 (PID %d) finished, exit code = %d\n",
               specific, WEXITSTATUS(status));
    }

    return 0;
}

