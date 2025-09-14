#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) {
        execl("/bin/ls", "ls", (char *)NULL);
        return 1; // Runs only if execl fails
    }

    pid2 = fork();
    if (pid2 == 0) {
        execl("/bin/date", "date", (char *)NULL);
        return 1; // Runs only if execl fails
    }

    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    printf("Parent process done\n");

    return 0;
}

