/* Fork - File Descriptor Access and Alter 

✅ Both processes share the same open file descriptor!
They both write into the same file test.txt at current file offset.
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_RDWR | O_CREAT, 0666);
    write(fd, "Hello", 5);

    pid_t pid = fork();

    if (pid == 0) { // Child
        write(fd, " Child", 6);
        printf("Child write done!!!\n");
    } else { // Parent
        write(fd, " Parent", 7);
        printf("Parent write done!!!\n");
    }

    return 0;
}