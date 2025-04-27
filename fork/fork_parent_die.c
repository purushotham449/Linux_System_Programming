/*  Fork - What Happens if Parent Dies Before Child? (Orphan Process)

        If a parent process terminates before its child,
        The child becomes an orphan.
        Kernel reassigns the child to the init (PID 1) process (or systemd nowadays).
        init or systemd wait()s for the child later to clean it up properly.

    getppid() shows 1 because systemd/init adopted the child!

Parent process dies
     ↓
Child becomes orphan
     ↓
init (PID 1) adopts the child
     ↓
init automatically wait()s for child's exit

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        sleep(60);  // Child sleeps while parent exits
        printf("Child (PID: %d), new parent PID: %d\n", getpid(), getppid());
        _exit(0);
    } else {
        printf("Parent (PID: %d) exiting...\n", getpid());
        sleep(30);
        exit(0);
    }
}