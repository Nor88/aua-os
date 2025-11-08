#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(void) {
    const char *filename = "sparse.bin";
    int fd;
    const char *start = "START";
    const char *end   = "END";
    off_t final_size;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "Error opening %s: %s\n", filename, strerror(errno));
        return 1;
    }

    if (write(fd, start, strlen(start)) != (ssize_t)strlen(start)) {
        fprintf(stderr, "Error writing START: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    if (lseek(fd, 1024 * 1024, SEEK_CUR) == (off_t)-1) {
        fprintf(stderr, "Error seeking forward: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    if (write(fd, end, strlen(end)) != (ssize_t)strlen(end)) {
        fprintf(stderr, "Error writing END: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    close(fd);

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error reopening %s: %s\n", filename, strerror(errno));
        return 1;
    }

    final_size = lseek(fd, 0, SEEK_END);
    if (final_size == (off_t)-1) {
        fprintf(stderr, "Error getting file size: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    printf("Apparent file size: %ld bytes\n", (long)final_size);

    close(fd);
    return 0;
}

