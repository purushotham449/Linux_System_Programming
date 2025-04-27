/* clone() + mmap() ➔ Shared Memory

✅ Using mmap() we create a shared memory region between parent and child created with clone().
✅ Both can read/write to the same memory directly — no pipes needed!

Technique           | What happens
--------------------------------------------------------------------------
mmap()              | Creates shared memory between processes
clone()             | Child process uses same memory
Parent and Child    | Communicate without pipes, just memory updates

*/

// clone_mmap.c
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

#define STACK_SIZE (1024 * 1024)

char *shared_mem;

int child_fn(void *arg) {
    printf("Child: PID = %d\n", getpid());
    sleep(1); // Let parent write first
    printf("Child read from shared memory: %s\n", shared_mem);
    strcpy(shared_mem, "Child updated this message!");
    printf("Child write done!!!!\n");
    return 0;
}

int main() {
    // Create shared memory region
    shared_mem = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap");
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

    printf("Parent: PID = %d\n", getpid());
    strcpy(shared_mem, "Hello from parent!");
    printf("Parent write done!!!!\n");
    sleep(2); // Let child update
    printf("Parent sleeping\n");

    printf("Parent reads from shared memory: %s\n", shared_mem);

    free(stack);
    munmap(shared_mem, 4096);
    return 0;
}