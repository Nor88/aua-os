#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(void) {
    char src_path[256], dest_path[256];
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];
    ssize_t total_bytes = 0;

    printf("Enter source file path: ");
    if (scanf("%255s", src_path) != 1) {
        fprintf(stderr, "Error: invalid source path input\n");
        return 1;
    }

    printf("Enter destination file path: ");
    if (scanf("%255s", dest_path) != 1) {
        fprintf(stderr, "Error: invalid destination path input\n");
        return 1;
    }

     src_fd = open(src_path, O_RDONLY);
    if (src_fd < 0) {
        fprintf(stderr, "Error opening source file '%s': %s\n", src_path, strerror(errno));
        return 1;
    }

    dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        fprintf(stderr, "Error opening destination file '%s': %s\n", dest_path, strerror(errno));
        close(src_fd);
        return 1;
    }

    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written < 0) {
            fprintf(stderr, "Error writing to destination file: %s\n", strerror(errno));
            close(src_fd);
            close(dest_fd);
            return 1;
        }
        total_bytes += bytes_written;
    }

    if (bytes_read < 0) {
        fprintf(stderr, "Error reading from source file: %s\n", strerror(errno));
        close(src_fd);
        close(dest_fd);
        return 1;
    }

    close(src_fd);
    close(dest_fd);

    printf("Copied %zd bytes from '%s' to '%s'\n", total_bytes, src_path, dest_path);
    return 0;

}
