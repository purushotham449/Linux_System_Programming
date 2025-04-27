/*  Synchronous Waiting: Suspend Parent Until Child Terminates

Parent calls wait() or waitpid().
Parent is blocked until the child exits

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child working...\n");
        sleep(5);
        printf("Child done.\n");
        _exit(0);
    } else {
        printf("Parent waiting for child...\n");
        wait(NULL);  // Parent suspends here
        printf("Parent: Child exited!\n");
    }
    return 0;
}