/* Using pthread_sigmask() - unblock and sigwait()*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define NUM_THREADS 2

// Signal handler function
void* thread_func(void* arg) {
    sigset_t sigset;
    int sig;

    // Block SIGINT in this thread
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);

    printf("Thread %ld: Waiting for SIGINT...\n", (long)arg);

    // Wait for SIGINT to be received
    sigwait(&sigset, &sig);
    printf("Thread %ld: Received SIGINT\n", (long)arg);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    sigset_t sigset;

    // Initialize the signal set
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);

    // Block SIGINT in the main thread
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);

    // Create threads
    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, (void*)i) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Give the threads some time to block SIGINT and wait for it
    sleep(1);

    // Unblock SIGINT in the main thread so threads can receive it
    pthread_sigmask(SIG_UNBLOCK, &sigset, NULL);

    // Sleep for a while to let threads handle the signal
    sleep(5);

    // Clean up threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}