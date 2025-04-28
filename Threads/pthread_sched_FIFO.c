/* Pthread Scheduling Policy - FIFO

✅ Two threads are created
✅ Both use Scheduling Policy = SCHED_FIFO (First-In-First-Out, real-time scheduling)
✅ We explicitly set thread priority manually.

Why?
--------------------------------------------------------------------------------------------

In SCHED_FIFO:

    Higher-priority threads preempt lower-priority ones.
    If a high-priority thread is ready, the CPU always runs it.
    Lower-priority thread gets CPU only after higher-priority thread blocks or exits

Concept                         | Explanation
--------------------------------------------------------------------------------------------

SCHED_FIFO                      | Real-time scheduling, strict priority
PTHREAD_EXPLICIT_SCHED          | Force using our custom scheduling, not inherit
Root required                   | Because real-time scheduling affects system responsiveness

*/

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

void* thread_func(void* arg) {
    int thread_num = *((int*)arg);

    for (int i = 0; i < 5; i++) {
        printf("Thread %d running iteration %d\n", thread_num, i+1);
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_attr_t attr1, attr2;
    struct sched_param param1, param2;
    int policy = SCHED_FIFO;
    int thread_num1 = 1, thread_num2 = 2;

    // Initialize thread attributes
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    // Set scheduling policy
    pthread_attr_setschedpolicy(&attr1, policy);
    pthread_attr_setschedpolicy(&attr2, policy);

    // Set explicit scheduling (otherwise PTHREAD_INHERIT_SCHED is default)
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    // Set priority (must be within range for SCHED_FIFO)
    int max_priority = sched_get_priority_max(policy);

    param1.sched_priority = max_priority;       // Higher priority
    param2.sched_priority = max_priority - 1;   // Lower priority

    pthread_attr_setschedparam(&attr1, &param1);
    pthread_attr_setschedparam(&attr2, &param2);

    // Create threads
    pthread_create(&t1, &attr1, thread_func, &thread_num1);
    pthread_create(&t2, &attr2, thread_func, &thread_num2);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy attributes
    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);

    return 0;
}