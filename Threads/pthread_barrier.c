/* pthread Barrier - All threads wait until barrier is crossed

✅ Threads wait at barrier until all 3 are ready ➔ Then continue

*/

#include <pthread.h>
#include <stdio.h>

pthread_barrier_t barrier;

void* threadFunc(void* arg) {
    printf("Thread %lu waiting at barrier \n", pthread_self());
    pthread_barrier_wait(&barrier);
    printf("Thread %lu passed barrier\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    pthread_barrier_init(&barrier, NULL, 3);

    pthread_create(&t1, NULL, threadFunc, NULL);
    pthread_create(&t2, NULL, threadFunc, NULL);
    pthread_create(&t3, NULL, threadFunc, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_barrier_destroy(&barrier);
    return 0;
}