/* Two Threads + Mutex trylock */

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;

void* increment(void* arg) {
    int* counter = (int*)arg;
    
    for (int i = 0; i < 5; i++) {
        if (pthread_mutex_trylock(&lock) == 0) {
            printf("Got lock!\n");
            (*counter)++;
            printf("Thread %lu incremented counter to %d\n", pthread_self(), *counter);
            pthread_mutex_unlock(&lock);
        } else {
            printf("Didn't get lock\n");
        }
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int counter = 0;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, &counter);
    pthread_create(&t2, NULL, increment, &counter);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Main: Final counter value = %d\n", counter);
    return 0;
}