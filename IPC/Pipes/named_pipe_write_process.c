/* IPC - Named pipes (also known as FIFOs)

Named pipes (also known as FIFOs) are similar to pipes but allow communication between unrelated processes. 
They have a name in the filesystem

One process writes to a FIFO, and another process reads from it

*/

// Writer process
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *fifo_path = "/tmp/my_fifo";
    int fd = open(fifo_path, O_WRONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    const char *msg = "Hello from writer!";
    write(fd, msg, strlen(msg) + 1);  // Write message to FIFO
    close(fd);

    return 0;
}