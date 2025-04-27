/*  Error: fork first, then open file descriptor in child

Normally: fork() copies file descriptors.

If child process tries to open a file after fork() but something is broken 
(like file permissions, wrong path, or resources exhausted), open() will fail, and perror() will print the error

*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child
        int fd = open("/nonexistentfile.txt", O_RDONLY);
        if (fd == -1) {
            perror("Child: open failed");
        }
        _exit(0);
    } else {
        // Parent
        wait(NULL);
        printf("Parent exiting.\n");
    }
}