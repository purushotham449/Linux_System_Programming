/*  Clone - Zombie / Orphan

✅ If parent does not wait for child, the child becomes Zombie.
*/

// clone_zombie.c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define STACK_SIZE (1024 * 1024)

int child_fn(void *arg) {
    printf("Child: PID = %d\n", getpid());
    printf("Child exiting\n");
    return 0;
}

int main() {
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

    printf("Parent: PID = %d, Child PID = %d\n", getpid(), pid);

    // Parent is sleeping and NOT calling waitpid()
    sleep(10);

    printf("Parent exiting\n");

    free(stack);
    return 0;
}