/* Fork - Synchronous - Local & Global Variable

✅ Changes in child do not affect parent (memory was copied)
*/

#include <stdio.h>
#include <unistd.h>

int global_var = 100;

int main() {
    int local_var = 50;

    pid_t pid = fork();

    if (pid == 0) { // Child
        global_var++;
        local_var++;
        printf("Child pid = %d\n", pid);
        printf("[Child] global_var = %d, local_var = %d\n", global_var, local_var);
    } else { // Parent
        sleep(1); // So child runs first
        printf("Parent pid = %d\n", pid);
        printf("[Parent] global_var = %d, local_var = %d\n", global_var, local_var);
    }

    return 0;
}