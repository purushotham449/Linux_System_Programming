/* Later detached

✅ Detached thread will auto-clean after exit.

*/

#include <pthread.h>
#include <stdio.h>

void* worker(void* arg) {
    printf("Detached worker thread\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, worker, NULL);
    pthread_detach(tid); // Detach to auto-reclaim resources
    printf("Main exits cleanly\n");
    return 0;
}