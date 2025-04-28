/* Handling SIGINT in a dedicated signal thread using sigwait 

How it works:
---------------------------------------------------------------------------------

Step     | Detail
---------------------------------------------------------------------------------
1        | Main thread blocks SIGINT.
2        | Worker thread inherits blocking.
3        | Dedicated signal thread uses sigwait() to wait for SIGINT.
4        | When you press Ctrl+C, sigwait() returns, thread handles the signal.

Why sigwait() is better?

Old Style                       | New Style
---------------------------------------------------------------------------------
signal(), sigaction()           | sigwait()
Async (unpredictable)           | Sync (safe & predictable)
Can happen anytime              | Handled neatly inside a thread

Summary table

Concept                                    | Usage
---------------------------------------------------------------------------------
pthread_sigmask(SIG_BLOCK, &set, NULL)     | Block signals for all threads.
sigwait(set, &sig)                         | Wait synchronously for signal.
sigwaitinfo(set, &siginfo)                 | Like sigwait, but gets extra info (sender PID etc).

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void* signal_handler_thread(void* arg) {
    sigset_t *set = (sigset_t*) arg;
    int sig;

    printf("Signal handling thread started\n");

    // Wait for signal
    if (sigwait(set, &sig) == 0) {
        printf("Received signal %d\n", sig);
        if (sig == SIGINT) {
            printf("Handling SIGINT (Ctrl+C), exiting gracefully.\n");
            exit(0);
        }
    } else {
        perror("sigwait");
    }
    return NULL;
}

void* worker_thread(void* arg) {
    while (1) {
        printf("Worker thread running...\n");
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t sig_thread, work_thread;
    sigset_t set;

    // Block SIGINT in the whole process (main + threads)
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0) {
        perror("pthread_sigmask");
        exit(EXIT_FAILURE);
    }

    // Create the worker thread
    pthread_create(&work_thread, NULL, worker_thread, NULL);

    // Create the signal handler thread
    pthread_create(&sig_thread, NULL, signal_handler_thread, (void*)&set);

    // Wait for threads
    pthread_join(work_thread, NULL);
    pthread_join(sig_thread, NULL);

    return 0;
}