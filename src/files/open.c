#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;

int main()
{
    int fd;
    errno = 0;
    fd = open("my_file.txt", O_RDONLY );
    //fd = open("my_file.txt", O_RDONLY | O_CREAT, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
    if (fd == -1)
    {
        perror("");
    }
    return 0;
}