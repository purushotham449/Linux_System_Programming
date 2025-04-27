/* Using clone create Threads Manually

✅ We'll create two threads manually without using pthread_create()!
✅ Threads will share memory, file descriptors, etc.
*/

// thread_clone.c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define STACK_SIZE (1024 * 1024)  // 1 MB stack

int global_var = 0;

int thread_fn(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d: PID = %d, global_var = %d\n", id, getpid(), global_var);
    global_var += id;
    printf("Thread %d: Updated global_var = %d\n", id, global_var);
    return 0;
}

int main() {
    char *stack1 = malloc(STACK_SIZE);
    char *stack2 = malloc(STACK_SIZE);
    if (!stack1 || !stack2) {
        perror("malloc");
        exit(1);
    }

    int id1 = 1, id2 = 2;

    int flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD | SIGCHLD;

    clone(thread_fn, stack1 + STACK_SIZE, flags, &id1);
    clone(thread_fn, stack2 + STACK_SIZE, flags, &id2);

    sleep(1); // Let the threads finish
    printf("Main thread: global_var = %d\n", global_var);

    free(stack1);
    free(stack2);
    return 0;
}