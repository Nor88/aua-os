#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        execl("/bin/grep", "grep", "main", "test.txt", (char *)NULL);
        perror("execl failed");
        return 1;
    } 
    else if (pid > 0) {
        wait(NULL);
        printf("Parent process completed\n");
    } 
    else {
        perror("fork failed");
        return 1;
    }

    return 0;
}

