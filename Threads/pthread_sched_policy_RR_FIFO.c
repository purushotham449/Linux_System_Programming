/* pthread Scheduling Policy Demo (FIFO and Round Robin)

Two threads with different scheduling policies

Important Notes:

    Must run as root (sudo ./a.out) to set real-time policies like SCHED_FIFO or SCHED_RR.
    If both threads have same priority, Round-Robin threads will get time slices.
    FIFO will continue until preempted (unlikely unless it yields or sleeps)

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

void* thread_func(void* arg) {
    int num = *((int*)arg);
    printf("Thread %d is running\n", num);
    while(1) {
        printf("Thread %d working...\n", num);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_attr_t attr1, attr2;
    struct sched_param param1, param2;
    int id1 = 1, id2 = 2;

    // Initialize thread attributes
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    // Set scheduling policy
    pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);   // Thread 1 : FIFO
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);     // Thread 2 : Round Robin

    // Set scheduling parameters (priority)
    param1.sched_priority = 20;
    param2.sched_priority = 20;  // Must be same or different depending on test

    pthread_attr_setschedparam(&attr1, &param1);
    pthread_attr_setschedparam(&attr2, &param2);

    // Explicit scheduling instead of inheriting
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    // Create threads
    if (pthread_create(&t1, &attr1, thread_func, &id1) != 0) {
        perror("pthread_create for thread 1");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&t2, &attr2, thread_func, &id2) != 0) {
        perror("pthread_create for thread 2");
        exit(EXIT_FAILURE);
    }

    // Wait for threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy attributes
    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);

    return 0;
}