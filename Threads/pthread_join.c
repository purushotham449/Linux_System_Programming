/* Create and Join a Thread 

✅ This is synchronous — parent will suspend until the thread exits.

*/

#include <stdio.h>
#include <pthread.h>

void* thread_function(void* arg) {
    printf("Thread: Hello from thread! Received value = %d\n", *(int*)arg);
    return NULL;
}

int main() {
    pthread_t tid;
    int value = 42;

    // Create thread
    if (pthread_create(&tid, NULL, thread_function, &value) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Wait for thread to finish
    pthread_join(tid, NULL);

    printf("Main: Thread finished. Exiting.\n");
    return 0;
}