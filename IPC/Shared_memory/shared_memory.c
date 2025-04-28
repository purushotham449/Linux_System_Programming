/* Shared Memory allows multiple processes to access the same portion of memory. It is one of the fastest IPC mechanisms because the data does not need to be copied between processes.

Example: One process writes data to shared memory, and another process reads it

Explanation:

    shmget  : Create a shared memory segment.
    shmat   : Attach the shared memory to the process's address space.
    shmdt   : Detach the shared memory from the process's address space.
    shmctl  : Perform control operations on shared memory (e.g., remove it).
    
*/

#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65);  // Generate a unique key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);  // Allocate shared memory

    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    char *str = (char*)shmat(shmid, NULL, 0);  // Attach to shared memory
    strcpy(str, "Hello from shared memory!");

    printf("Writing to shared memory: %s\n", str);
    shmdt(str);  // Detach from shared memory

    // Now, another process can read from this shared memory.

    return 0;
}