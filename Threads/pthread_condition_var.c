/* pthread Condition Variable - Used for signaling between threads

cond wait and signal
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0;

void* worker(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Thread got a lock!!!\n");
    while (!ready)
        // printf("Thread condition wait!!!\n");
        pthread_cond_wait(&cond, &mutex);
    printf("Worker: Condition satisfied!\n");
    pthread_mutex_unlock(&mutex);
    printf("Thread got a unlock!!!\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, worker, NULL);

    sleep(2); // Simulate work
    pthread_mutex_lock(&mutex);
    printf("Main got a lock!!!\n");
    ready = 1;
    pthread_cond_signal(&cond); // Wake up worker
    pthread_mutex_unlock(&mutex);
    printf("Main got a unlock!!!\n");

    pthread_join(tid, NULL);
    return 0;
}