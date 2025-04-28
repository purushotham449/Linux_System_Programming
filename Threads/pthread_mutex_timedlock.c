/* Two Threads + Mutex timedlock */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* increment(void* arg) {
    int* counter = (int*)arg;

    for (int i = 0; i < 5; i++) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 2; // 2 seconds timeout from now

        sleep(3);
        if (pthread_mutex_timedlock(&lock, &ts) == 0) {
            printf("Got lock!\n");
            (*counter)++;
            printf("Thread %lu incremented counter to %d\n", (unsigned long)pthread_self(), *counter);
            pthread_mutex_unlock(&lock); // Correct unlock
        } else {
            printf("Didn't get lock (timeout)\n");
        }

        sleep(1); // Optional: Sleep a bit before next try
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int counter = 0;

    pthread_create(&t1, NULL, increment, &counter);
    pthread_create(&t2, NULL, increment, &counter);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value = %d\n", counter);

    pthread_mutex_destroy(&lock);
    return 0;
}