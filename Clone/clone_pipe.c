/* Using clone() + pipe() for IPC (Inter Process Communication)

✅ Here, parent writes to pipe and child reads from pipe.
*/

// clone_pipe.c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define STACK_SIZE (1024 * 1024)

int pipefd[2];

int child_fn(void *arg) {
    close(pipefd[1]);  // Close write end in child
    char buffer[100];
    read(pipefd[0], buffer, sizeof(buffer));
    printf("Child received: %s\n", buffer);
    close(pipefd[0]);
    return 0;
}

int main() {
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    char *stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("malloc");
        exit(1);
    }

    pid_t pid = clone(child_fn, stack + STACK_SIZE, SIGCHLD, NULL);
    if (pid == -1) {
        perror("clone");
        exit(1);
    }

    close(pipefd[0]);  // Close read end in parent
    char *msg = "Hello from parent!";
    write(pipefd[1], msg, strlen(msg) + 1);
    printf("Parent written: %s\n", msg);
    close(pipefd[1]);

    sleep(1); // Allow child to read

    free(stack);
    return 0;
}