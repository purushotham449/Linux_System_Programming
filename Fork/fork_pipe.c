/* Fork - Using pipe() - Communication Between Child & Parent

✅ Pipes provide unidirectional communication between parent and child
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pipe(fd); // Create a pipe

    pid_t pid = fork();

    if (pid == 0) { // Child
        close(fd[0]); // Close reading end
        char msg[] = "Hello Parent";
        write(fd[1], msg, strlen(msg) + 1);
        printf("[Child write]: %s\n", msg);
        close(fd[1]); // Close writing end
    } else { // Parent
        close(fd[1]); // Close writing end
        char buf[100];
        read(fd[0], buf, sizeof(buf));
        printf("[Parent] Received from child: %s\n", buf);
        close(fd[0]); // Close reading end
    }

    return 0;
}