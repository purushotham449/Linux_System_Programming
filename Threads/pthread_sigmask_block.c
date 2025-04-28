/* sigmask — Block SIGINT in a thread

✅ Main & Thread will not be interrupted by Ctrl+C

Scenario                                            | Result
Block SIGINT in main before threads                 | Ctrl+C has no effect!
Block only inside thread                            | Ctrl+C still kills via main thread

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void* thread_func(void* arg) {
    printf("Thread started, SIGINT should be blocked.\n");

    while (1) {
        printf("Thread running...\n");
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t thread;
    sigset_t set;

    // Block SIGINT for this (main) thread
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0) {
        perror("pthread_sigmask");
        exit(EXIT_FAILURE);
    }
    printf("Blocked SIGINT in main thread\n");

    // Now create a new thread
    if (pthread_create(&thread, NULL, thread_func, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Wait forever (no SIGINT will kill process)
    pthread_join(thread, NULL);

    return 0;
}