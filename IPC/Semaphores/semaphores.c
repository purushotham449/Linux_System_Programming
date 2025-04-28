/* Semaphores are used to control access to a shared resource by multiple processes. A semaphore can be thought of as a counter, and it is primarily used for synchronization purposes.

Example: Use semaphores to control access to a critical section

Explanation:

    sem_init     : Initialize the semaphore.
    sem_wait     : Wait (decrease) the semaphore. If the semaphore value is 0, the thread will block.
    sem_post     : Signal (increase) the semaphore, potentially unblocking a waiting thread.
    sem_destroy  : Clean up the semaphore.

*/

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t sem;

void* thread_func(void* arg) {
    sem_wait(&sem);  // Decrease the semaphore value
    printf("Thread ID: %lu\n", pthread_self());
    printf("In critical section\n");
    sleep(1);
    printf("Leaving critical section\n");
    sem_post(&sem);  // Increase the semaphore value
    return NULL;
}

int main() {
    pthread_t threads[3];
    sem_init(&sem, 0, 1);  // Initialize semaphore with value 1

    // Create threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    // Join threads
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem);  // Destroy the semaphore
    return 0;
}