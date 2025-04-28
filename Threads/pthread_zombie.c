/* Joinable State

By default, a thread is joinable.
If NOT joined (Resource leak):

❌ No pthread_join ➔ thread becomes a zombie and leaks resources.

*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* worker(void* arg) {
    printf("Worker thread running\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, worker, NULL);
    sleep(1); // Thread ends but we didn't join or detach
    printf("Main exiting without joining ➔ Resource leak!\n");
    return 0;
}