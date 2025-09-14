#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
    printf("Start of program: PID=%d\n", getpid());
    
    fork();
    printf("After first fork: PID=%d, PPID=%d\n", getpid(), getppid());

    fork();
    printf("After second fork: PID=%d, PPID=%d\n", getpid(), getppid());

    fork();
    printf("After third fork: PID=%d, PPID=%d\n", getpid(), getppid());

    fork();
    printf("After fourth fork: PID=%d, PPID=%d\n", getpid(), getppid());

    fork();
    printf("After fifth fork: PID=%d, PPID=%d\n", getpid(), getppid());

   
    return 0;
}
