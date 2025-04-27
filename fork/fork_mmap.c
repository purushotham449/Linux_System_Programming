/* Fork - Using mmap() — Child Writes, Parent Reads

✅ With mmap, child and parent can communicate via memory directly

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main() {
    char *shared_mem = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    pid_t pid = fork();

    if (pid == 0) { // Child
        strcpy(shared_mem, "Hello from Child");
        printf("Child write done!!!\n");
    } else { // Parent
        sleep(1); // Wait for child to write
        printf("[Parent] Read from shared memory: %s\n", shared_mem);
        printf("Parent read done!!!\n");
    }

    munmap(shared_mem, 100);
    return 0;
}