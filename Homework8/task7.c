#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    char f1[256], f2[256];
    int fd1, fd2;
    unsigned char b1, b2;
    off_t index = 0;
    ssize_t r1, r2;

    printf("Enter first file path: ");
    scanf("%255s", f1);
    printf("Enter second file path: ");
    scanf("%255s", f2);

   fd1 = open(f1, O_RDONLY);
   if(fd1 < 0){perror("Open first"); return 1;}
   fd2 = open(f2, O_RDONLY);
   if(fd2 < 0){perror("Open second"); return 1;}

   while(1){
	  r1 = read(fd1, &b1, 1);
	  r2 = read(fd2, &b2, 1);

	  if(r1 == 0 && r2 == 0){
		 printf("Files are identical\n");
		 break;
	  }

	  if(r1 == 0 || r2 == 0 || b1 != b2){
		 printf("Files differ at byte %ld\n", (long)index);
		 close(fd1);
		 close(fd2);
		 return 1;
	  }

	  index++;
   }

   close(fd1);
   close(fd2);

   return 0;
} 

