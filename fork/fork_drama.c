/* Fork Goals:

    Create Zombie
    Handle Zombie with wait()
    Create Orphan
    Communication between Parent ↔ Child (pipe)
    Async Child exit signal handling (SIGCHLD)

What Happens Step by Step?

    ✅ 1. Parent and child created using fork().
    ✅ 2. Child writes a message to parent using pipe.
    ✅ 3. Child exits after some time (becomes Zombie momentarily).
    ✅ 4. Parent doesn't immediately call wait(), but SIGCHLD handler automatically reaps child using waitpid().
        So: NO zombies!
    ✅ 5. If parent dies later, child would have become orphan (if it was still alive).

Concept                 | Where It's Used
-----------------------------------------------------------------------
fork()                  | Creating child
pipe()                  | Child sends message to parent
signal(SIGCHLD)         | Parent handles child exit asynchronously
waitpid(-1, WNOHANG)    | Non-blocking reaping of any terminated child
Zombie Avoidance        | Because parent reaps child immediately
Orphan Scenario         | (If parent exits early)

*/

// family_drama.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void sigchld_handler(int sig) {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("[SIGCHLD Handler] Child %d terminated\n", pid);
    }
}

int main() {
    int pipefd[2];
    pid_t pid;

    // Setup SIGCHLD handler to avoid zombies
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("[Child] I am child (PID: %d), parent PID: %d\n", getpid(), getppid());

        close(pipefd[0]); // Close read end

        sleep(2); // Pretend doing some work
        char msg[] = "Hello Parent, I am your child!";
        write(pipefd[1], msg, sizeof(msg));
        printf("[Child] Message sent to parent.\n");

        sleep(2); // Still alive

        printf("[Child] Exiting now...\n");
        _exit(0);

    } else {
        // Parent process
        printf("[Parent] I am parent (PID: %d), child PID: %d\n", getpid(), pid);

        close(pipefd[1]); // Close write end

        sleep(5); // Let child exit first

        char buffer[100];
        int bytes = read(pipefd[0], buffer, sizeof(buffer));
        if (bytes > 0) {
            buffer[bytes] = '\0'; // Null terminate
            printf("[Parent] Received message: %s\n", buffer);
        } else {
            printf("[Parent] No message received.\n");
        }

        printf("[Parent] Doing some other work...\n");
        sleep(5);

        printf("[Parent] Exiting.\n");
    }

    return 0;
}