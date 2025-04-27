/*  Normal clone() (no sharing) → behaves like fork()

✅ Child gets copy, not shared memory.
✅ Acts like fork().
✅ Child and parent have separate memory.

*/

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int child_fn(void *arg) {
    printf("Child: PID = %d\n", getpid());
    return 0;
}

int main() {
    char *stack = malloc(1024*1024); // Allocate stack for child
    if (!stack) {
        perror("malloc");
        exit(1);
    }

    pid_t pid = clone(child_fn, stack + 1024*1024, SIGCHLD, NULL);
    if (pid == -1) {
        perror("clone");
        exit(1);
    }

    printf("Parent: PID = %d, Child PID = %d\n", getpid(), pid);
    sleep(1);

    return 0;
}