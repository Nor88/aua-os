#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process: run ls
        execl("/bin/ls", "ls", (char *)NULL);
    } else {
        // Parent process: wait for child to finish
        wait(NULL);
        printf("Parent process done\n");
    }

    return 0;
}

