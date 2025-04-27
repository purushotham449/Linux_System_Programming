/*  How to Prevent Zombie Process Using SIGCHLD and SA_NOCLDWAIT

Normally when a child exits:

    1. It becomes Zombie if the parent does not call wait().
    2. To prevent Zombie automatically, we can tell the kernel:
    ❝ Hey! Don't even keep child status. I don't care. ❞

We do this by:

    1. Setting the SA_NOCLDWAIT flag when handling SIGCHLD.
    2. Then child exit won't create a Zombie!

No Zombie created!
ps aux will show only the parent running.

*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    struct sigaction sa;
    sa.sa_handler = SIG_IGN; // Ignore SIGCHLD
    sa.sa_flags = SA_NOCLDWAIT; // No zombie
    sigaction(SIGCHLD, &sa, NULL);

    pid_t pid = fork();

    if (pid == 0) {
        printf("Child (PID %d) exiting...\n", getpid());
        _exit(0);
    } else {
        printf("Parent (PID %d) sleeping...\n", getpid());
        sleep(10);
    }

    return 0;
}