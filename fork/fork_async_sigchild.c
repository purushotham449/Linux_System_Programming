/*  Asynchronous: Child Terminates, Kernel Sends Signal (SIGCHLD)

When a child terminates, kernel sends SIGCHLD to the parent asynchronously.
Parent can handle SIGCHLD to reap child without blocking.

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigchld_handler(int signum) {
    int status;
    pid_t pid = wait(&status); // Reap child
    printf("Child %d terminated!\n", pid);
}

int main() {
    signal(SIGCHLD, sigchld_handler); // Register handler

    pid_t pid = fork();

    if (pid == 0) {
        printf("Child process running...\n");
        sleep(3);
        printf("Child exiting...\n");
        _exit(0);
    } else {
        printf("Parent doing other work...\n");
        while (1) {
            printf("Parent busy...\n");
            sleep(1);
        }
    }
}