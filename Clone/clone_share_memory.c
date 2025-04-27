/* Clone- Share memory (CLONE_VM)

✅ Parent and child share memory address space!
✅ Because memory is shared!
*/

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int global_var = 5;

int child_fn(void *arg) {
    printf("Child before: global_var = %d\n", global_var);
    global_var = 100;
    printf("Child after: global_var = %d\n", global_var);
    return 0;
}

int main() {
    char *stack = malloc(1024*1024);
    if (!stack) exit(1);

    // Parent and child share memory address space!
    pid_t pid = clone(child_fn, stack + 1024*1024, CLONE_VM | SIGCHLD, NULL);
    sleep(1);

    printf("Parent sees global_var = %d\n", global_var);

    return 0;
}