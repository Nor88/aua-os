#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main(){
	const char *filename = "data.txt";
	const char *text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int fd;
	off_t size_before, size_after;
	char buffer[27];
	ssize_t bytes_read;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if(fd < 0){
		fprintf(stderr, "Error opening %s for writing: %s\n", filename, strerror(errno));
		return 1;
	}
	if(write(fd, text, strlen(text)) != (ssize_t)strlen(text)){
		fprintf(stderr, "Error writing to %s: %s\n", filename, strerror(errno));
		close(fd);
		return 1;
	}

	close(fd);

	fd = open(filename, O_RDWR);
   	if (fd < 0) {
        	fprintf(stderr, "Error reopening %s: %s\n", filename, strerror(errno));
        	return 1;
    	}

	size_before = lseek(fd, 0, SEEK_END);
    	if (size_before == (off_t)-1) {
       		fprintf(stderr, "Error getting file size: %s\n", strerror(errno));
        	close(fd);
        	return 1;
 	}
	
	printf("Original size: %ld bytes\n", (long)size_before);

	if (ftruncate(fd, 10) < 0) {
        	fprintf(stderr, "Error truncating file: %s\n", strerror(errno));
        	close(fd);
        	return 1;
    	}

	size_after = lseek(fd, 0, SEEK_END);
    	printf("New size after truncation: %ld bytes\n", (long)size_after);

	if (lseek(fd, 0, SEEK_SET) == (off_t)-1) {
        	fprintf(stderr, "Error rewinding file: %s\n", strerror(errno));
        	close(fd);
        	return 1;
    	}

    	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    	if (bytes_read < 0) {
        	fprintf(stderr, "Error reading file: %s\n", strerror(errno));
        	close(fd);
        	return 1;
    	}

    	buffer[bytes_read] = '\0';


	printf("Remaining content: \"%s\"\n", buffer);

    	close(fd);
    	return 0;
}
