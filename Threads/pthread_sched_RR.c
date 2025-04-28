/* Pthread Scheduling Policy - RR

✅ Two threads
✅ Scheduling policy: SCHED_RR (Round-Robin)
✅ Explicit priority
✅ Observe timeslice behavior

✅ Threads alternate turns because Round-Robin time slices are given fairly.

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
        usleep(200000); // 200ms small sleep to simulate some work
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_attr_t attr1, attr2;
    struct sched_param param1, param2;
    int policy = SCHED_RR;
    int thread_num1 = 1, thread_num2 = 2;

    // Initialize thread attributes
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    // Set scheduling policy
    pthread_attr_setschedpolicy(&attr1, policy);
    pthread_attr_setschedpolicy(&attr2, policy);

    // Set explicit scheduling
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    // Set priority
    int max_priority = sched_get_priority_max(policy);

    param1.sched_priority = max_priority;
    param2.sched_priority = max_priority - 1;

    pthread_attr_setschedparam(&attr1, &param1);
    pthread_attr_setschedparam(&attr2, &param2);

    // Create threads
    pthread_create(&t1, &attr1, thread_func, &thread_num1);
    pthread_create(&t2, &attr2, thread_func, &thread_num2);

    // Wait for threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy attributes
    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);

    return 0;
}