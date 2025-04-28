/* sigmask — Unblock SIGINT in a thread

✅ 2 Threads
✅ pthread_sigmask() → Unblock a signal (like SIGINT) in a thread
✅ Show how signal unblocking in one thread allows it to receive Ctrl+C while others don't

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

void* thread_func_blocked(void* arg) {
    printf("Thread 1: %lu Blocking SIGINT\n", pthread_self());

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    for (int i = 0; i < 10; ++i) {
        printf("Thread 1 working...\n");
        sleep(1);
    }
    return NULL;
}

void* thread_func_unblocked(void* arg) {
    printf("Thread 2: %lu Unblocking SIGINT\n", pthread_self());

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &set, NULL);

    for (int i = 0; i < 10; ++i) {
        printf("Thread 2 working...\n");
        sleep(1);
    }
    return NULL;
}

void sigint_handler(int signo) {
    printf("\nReceived SIGINT (Ctrl+C) in thread %lu\n", pthread_self());
    exit(0);
}

int main() {
    pthread_t t1, t2;

    // Install signal handler for SIGINT
    signal(SIGINT, sigint_handler);

    pthread_create(&t1, NULL, thread_func_blocked, NULL);
    pthread_create(&t2, NULL, thread_func_unblocked, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}