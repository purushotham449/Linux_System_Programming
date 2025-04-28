/* Pthread Using Reader-Writer Lock

Multiple reader threads will access a shared resource.
A single writer thread will modify the shared resource, ensuring exclusive access when writing.


*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 1

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
int shared_resource = 0;  // Shared resource

// Reader thread function
void* reader_func(void* arg) {
    pthread_rwlock_rdlock(&rwlock); // Acquire read lock

    printf("Reader %ld: Accessing shared resource, value = %d\n", (long)arg, shared_resource);
    sleep(1); // Simulate reading operation

    pthread_rwlock_unlock(&rwlock); // Release read lock
    return NULL;
}

// Writer thread function
void* writer_func(void* arg) {
    pthread_rwlock_wrlock(&rwlock); // Acquire write lock

    shared_resource++;
    printf("Writer: Updating shared resource, new value = %d\n", shared_resource);
    sleep(1); // Simulate writing operation

    pthread_rwlock_unlock(&rwlock); // Release write lock
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    // Create reader threads
    for (long i = 0; i < NUM_READERS; i++) {
        if (pthread_create(&readers[i], NULL, reader_func, (void*)i) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Create writer threads
    for (long i = 0; i < NUM_WRITERS; i++) {
        if (pthread_create(&writers[i], NULL, writer_func, (void*)i) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy the read-write lock
    pthread_rwlock_destroy(&rwlock);

    return 0;
}