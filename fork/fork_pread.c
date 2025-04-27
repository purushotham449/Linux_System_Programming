/* fork - Using pread()

✅ pread reads without changing the file offset (good for parallel reads)
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("sample.txt", O_RDWR | O_CREAT, 0666);
    write(fd, "ABCDEFG", 7);

    pid_t pid = fork();
    
    if (pid == 0) { // Child
        char buf[4];
        pread(fd, buf, 3, 0); // Read 3 bytes starting at offset 0
        buf[3] = '\0';
        printf("[Child pread] %s\n", buf);
    } else { // Parent
        sleep(1);
        char buf[4];
        pread(fd, buf, 3, 3); // Read 3 bytes starting at offset 3
        buf[3] = '\0';
        printf("[Parent pread] %s\n", buf);
    }

    return 0;
}
