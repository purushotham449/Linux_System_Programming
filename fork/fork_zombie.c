/*  Fork - Zombie Process

When a child terminates but the parent does not call wait() or waitpid(), the child becomes a Zombie.
A Zombie still occupies an entry in the process table (holding exit status) until parent reaps i

After child exits, it becomes Zombie until parent exits or calls wait().
You can observe it using ps aux | grep Z
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child
        printf("Child (PID: %d) exiting...\n", getpid());
        _exit(0);  // Child exits immediately
    } else {
        // Parent
        printf("Parent (PID: %d) sleeping...\n", getpid());
        sleep(30); // Parent sleeps without calling wait()
    }

    return 0;
}