/*  fork - Read & Write using File Descriptor

✅ Both child and parent read different parts of the same file
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("sample.txt", O_RDWR | O_CREAT, 0666);
    write(fd, "ABCDEFG", 7);

    pid_t pid = fork();
    
    if (pid == 0) { // Child
        printf("Child pid = %d\n", pid);
        lseek(fd, 0, SEEK_SET);  // Move to beginning
        char buf[4];
        read(fd, buf, 3);
        buf[3] = '\0';
        printf("[Child Read] %s\n", buf);
    } else { // Parent
        printf("Parent pid = %d\n", pid);
        sleep(1);
        lseek(fd, 3, SEEK_SET);  // Move to 4th character
        char buf[4];
        read(fd, buf, 3);
        buf[3] = '\0';
        printf("[Parent Read] %s\n", buf);
    }

    return 0;
}