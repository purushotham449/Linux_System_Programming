/* Anonymous Pipe:

    Typically used between a parent and child process.
    Data is transferred in a FIFO (First In, First Out) manner.

    Parent writing to the pipe, child reading from it.

*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[128];

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {  // Parent process
        close(pipefd[0]);  // Close unused read end
        const char *msg = "Hello from parent!";
        write(pipefd[1], msg, strlen(msg) + 1);  // Write message to pipe
        printf("Parent write done!!!!!!!!\n");
        close(pipefd[1]);  // Close write end
    } else {  // Child process
        close(pipefd[1]);  // Close unused write end
        read(pipefd[0], buffer, sizeof(buffer));  // Read message from pipe
        printf("Child read done!!!!\n");
        printf("Child received: %s\n", buffer);
        close(pipefd[0]);  // Close read end
    }

    return 0;
}