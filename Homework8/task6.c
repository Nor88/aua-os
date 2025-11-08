#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(void) {
    const char *filename = "numbers.txt";
    int fd;
    char buf[64];
    off_t start4 = 0, end4 = 0, size;
    char ch;
    int line = 1;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); return 1; }

    for (int i = 1; i <= 10; i++) {
        int n = snprintf(buf, sizeof(buf), "%d\n", i);
        if (write(fd, buf, n) != n) { perror("write"); close(fd); return 1; }
    }
    close(fd);

    fd = open(filename, O_RDWR);
    if (fd < 0) { perror("open"); return 1; }

    while (read(fd, &ch, 1) == 1) {
        if (ch == '\n') line++;
        if (line == 4) { start4 = lseek(fd, 0, SEEK_CUR); break; }
    }

    while (read(fd, &ch, 1) == 1) {
        if (ch == '\n') { end4 = lseek(fd, 0, SEEK_CUR); break; }
    }


    size = lseek(fd, 0, SEEK_END);
    off_t rem_len = size - end4;
    char *remainder = malloc(rem_len);
    lseek(fd, end4, SEEK_SET);
    read(fd, remainder, rem_len);


    lseek(fd, start4, SEEK_SET);
    write(fd, "100\n", 4);
    write(fd, remainder, rem_len);

    ftruncate(fd, start4 + 4 + rem_len);
    close(fd);
    free(remainder);

    fd = open(filename, O_RDONLY);
    while ((size = read(fd, buf, sizeof(buf))) > 0)
        write(STDOUT_FILENO, buf, size);
    close(fd);
    return 0;
}

