/* To implement synchronization between two threads using 
a condition variable (pthread_cond_t) and a broadcast (pthread_cond_broadcast()), 
we can have one thread wait for a condition to be satisfied, 
and the second thread signal that condition. 
The second thread can use pthread_cond_broadcast() to notify all waiting threads

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0; // Shared variable used to signal readiness

// Thread function that waits for the condition
void* thread_func(void* arg) {
    pthread_mutex_lock(&mutex);

    while (ready == 0) { // Wait until ready is set to 1
        printf("Thread %ld: Waiting for condition...\n", (long)arg);
        pthread_cond_wait(&cond, &mutex);
    }

    printf("Thread %ld: Condition met, proceeding...\n", (long)arg);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

// Thread function that signals the condition
void* signal_thread(void* arg) {
    sleep(5);  // Simulate some work before signaling

    pthread_mutex_lock(&mutex);

    ready = 1;  // Set the condition variable to be true
    printf("Signal thread: Broadcasting condition...\n");

    // Notify all threads waiting on the condition
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_t signal_thread_id;

    // Create the waiting threads
    for (long i = 0; i < NUM_THREADS - 1; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, (void*)i) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Create the signaling thread
    if (pthread_create(&signal_thread_id, NULL, signal_thread, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Join the threads
    for (int i = 0; i < NUM_THREADS - 1; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_join(signal_thread_id, NULL);

    return 0;
}