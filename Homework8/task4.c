#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_INPUT 1024

int main(void) {
    const char *filename = "log.txt";
    int fd;
    char input[MAX_INPUT];
    ssize_t nread;
    pid_t pid = getpid();
    char header[64];
    char buffer[MAX_INPUT + 128];
    ssize_t total_written = 0;

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        fprintf(stderr, "Error opening %s: %s\n", filename, strerror(errno));
        return 1;
    }

     printf("Type a log message: ");
     fflush(stdout);

     nread = read(STDIN_FILENO, input, MAX_INPUT - 1);
     if (nread < 0) {
        fprintf(stderr, "Error reading input: %s\n", strerror(errno));
        close(fd);
        return 1;
     }
     input[nread] = '\0';
     if (nread > 0 && input[nread - 1] == '\n')
        input[nread - 1] = '\0';

 
     snprintf(header, sizeof(header), "PID=%d: ", pid);
     snprintf(buffer, sizeof(buffer), "%s%s\n", header, input);

     ssize_t to_write = strlen(buffer);
     ssize_t written = write(fd, buffer, to_write);
     if (written != to_write) {
        fprintf(stderr, "Error writing log entry: %s\n", strerror(errno));
        close(fd);
        return 1;
     }
     total_written += written;

     off_t offset = lseek(fd, 0, SEEK_CUR);
     if (offset == (off_t)-1) {
        fprintf(stderr, "Error getting file offset: %s\n", strerror(errno));
        close(fd);
        return 1;
     }

     printf("Wrote %zd bytes. Final file offset: %ld\n", total_written, (long)offset);

     close(fd);
     return 0;
}
