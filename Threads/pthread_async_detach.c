/* Asynchronous behavior (detach thread)

✅ Here the thread runs asynchronously and main doesn’t wait.

*/


#include <pthread.h>
#include <stdio.h>

void* asyncThread(void* arg) {
    printf("Thread: Running independently...\n");
    pthread_exit(NULL); // Exit cleanly
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, asyncThread, NULL);
    pthread_detach(tid);  // No join needed!

    printf("Main: Detached thread, exiting main.\n");
    return 0;
}