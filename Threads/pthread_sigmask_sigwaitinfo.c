/* Multiple Signals with sigwaitinfo()

Handling multiple signals using a dedicated signal thread

✅ We will handle:

    SIGINT (Ctrl+C)
    SIGTERM (kill command)
    SIGHUP (hangup signal)

✅ We will use sigwaitinfo() (similar to sigwait, but gives more detailed info like sender PID etc.)

Concept                             | Detail
------------------------------------------------------------------------------------------
sigwaitinfo()                       | Waits for a signal and gives extra info (siginfo).
Blocking signals early              | Ensures signals don't randomly kill any thread.
Dedicated thread handles signals    | Safe and clean.

Traditional                             | Modern Threaded Apps
------------------------------------------------------------------------------------------
signal(), kill(), async handlers        | pthread_sigmask, sigwait(), sigwaitinfo()
Random, race conditions                 | Safe, clean, predictable
One handler shared by all threads       | One dedicated thread safely waits for signals

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void* signal_handler_thread(void* arg) {
    sigset_t *set = (sigset_t*) arg;
    struct siginfo siginfo;
    int sig;

    printf("Signal handling thread started\n");

    while (1) {
        sig = sigwaitinfo(set, &siginfo);
        if (sig == -1) {
            perror("sigwaitinfo");
            continue;
        }

        printf("Received signal: %d from PID: %d\n", sig, siginfo.si_pid);

        if (sig == SIGINT) {
            printf("Handling SIGINT (Ctrl+C). Ignoring...\n");
        } else if (sig == SIGTERM) {
            printf("Handling SIGTERM. Terminating process.\n");
            exit(0);
        } else if (sig == SIGHUP) {
            printf("Handling SIGHUP. Reloading config (simulate).\n");
            // Simulate reloading configuration
        } else {
            printf("Unhandled signal %d\n", sig);
        }
    }
}

void* worker_thread(void* arg) {
    while (1) {
        printf("Worker thread doing work...\n");
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t sig_thread, work_thread;
    sigset_t set;

    // Block signals in main thread (and later in worker threads)
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);
    sigaddset(&set, SIGHUP);

    if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0) {
        perror("pthread_sigmask");
        exit(EXIT_FAILURE);
    }

    // Create a worker thread
    pthread_create(&work_thread, NULL, worker_thread, NULL);

    // Create the signal handling thread
    pthread_create(&sig_thread, NULL, signal_handler_thread, (void*)&set);

    // Wait for threads
    pthread_join(work_thread, NULL);
    pthread_join(sig_thread, NULL);

    return 0;
}
