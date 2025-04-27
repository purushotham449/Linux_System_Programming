/* Clone - Share file descriptors (CLONE_FILES)

✅ If child closes FD, parent also loses it!
✅ Because child closed FD, parent also lost it.
*/

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

int fd;

int child_fn(void *arg) {
    printf("Child closing file descriptor\n");
    close(fd);
    return 0;
}

int main() {
    char *stack = malloc(1024*1024);
    if (!stack) exit(1);

    fd = open("test.txt", O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    pid_t pid = clone(child_fn, stack + 1024*1024, CLONE_FILES | SIGCHLD, NULL);
    sleep(1);

    if (write(fd, "hello", 5) < 0) {
        perror("Parent write failed");
    } else {
        printf("Parent write success\n");
    }

    return 0;
}