#include <stdio.h>
#include <stdlib.h>   // for atexit(), exit()
#include <unistd.h>

void cleanup1(void) {
    printf("Cleanup function 1 called.\n");
}

void cleanup2(void) {
    printf("Cleanup function 2 called.\n");
}

int main() {
    if (atexit(cleanup1) != 0 || atexit(cleanup2) != 0) {
        perror("atexit registration failed");
        return 1;
    }

    printf("Main function started (PID = %d)\n", getpid());

    // Try calling exit() here to see the functions run
   // exit(0);

    printf("Main is finishing normally...\n");
    return 0;  // exit() is called automatically here
}

