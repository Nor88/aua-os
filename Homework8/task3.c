#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(void) {
    char filepath[256];
    int fd;
    off_t filesize;
    unsigned char ch;

    printf("Enter path to existing text file: ");
    if (scanf("%255s", filepath) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error opening file '%s': %s\n", filepath, strerror(errno));
        return 1;
    }

    filesize = lseek(fd, 0, SEEK_END);
    if (filesize == (off_t)-1) {
        fprintf(stderr, "Error determining file size: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    if(filesize == 0){
	    write(STDOUT_FILENO, "\n", 1);
	    close(fd);
	    return 0;
    }

    for (off_t pos = filesize - 1; pos >= 0; pos--) {
        if (lseek(fd, pos, SEEK_SET) == (off_t)-1) {
            fprintf(stderr, "Error seeking in file: %s\n", strerror(errno));
            close(fd);
            return 1;
        }

        if (read(fd, &ch, 1) != 1) {
            fprintf(stderr, "Error reading file: %s\n", strerror(errno));
            close(fd);
            return 1;
        }

        if (write(STDOUT_FILENO, &ch, 1) != 1) {
            fprintf(stderr, "Error writing to stdout: %s\n", strerror(errno));
            close(fd);
            return 1;
        }
    }

    write(STDOUT_FILENO, "\n", 1);

    close(fd);
    return 0;
}
