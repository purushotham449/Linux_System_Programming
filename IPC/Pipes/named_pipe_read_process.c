/* IPC - Named pipes (also known as FIFOs)

Named pipes (also known as FIFOs) are similar to pipes but allow communication between unrelated processes. 
They have a name in the filesystem

One process writes to a FIFO, and another process reads from it

*/

// Reader process
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *fifo_path = "/tmp/my_fifo";
    char buffer[128];

    // Open the FIFO for reading
    int fd = open(fifo_path, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    read(fd, buffer, sizeof(buffer));  // Read message from FIFO
    printf("Reader received: %s\n", buffer);
    close(fd);

    return 0;
}