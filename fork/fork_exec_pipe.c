/* fork() + exec() + pipe() Example

Suppose:

    Parent sends a message to child
    Child replaces itself with a new program (exec) and reads the message

✅ What happens here?

    Parent writes "Hello from Parent to New Process" into a pipe.
    Child becomes cat using exec — so now child is replaced with cat.
    cat reads from stdin (which is connected to the pipe!) and prints it.
*/

// parent_child_pipe_exec.c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        // Child
        printf("Child pid = %d\n", pid);
        close(fd[1]); // Close write end

        dup2(fd[0], STDIN_FILENO); // Make stdin come from pipe
        close(fd[0]);

        execlp("cat", "cat", NULL); // Replace child process with 'cat'
        perror("execlp failed");
    } else {
        // Parent
        printf("Parent pid = %d\n", pid);
        close(fd[0]); // Close read end
        char msg[] = "Hello from Parent to New Process\n";
        write(fd[1], msg, strlen(msg));
        close(fd[1]);

        wait(NULL); // Wait for child to finish
    }

    return 0;
}