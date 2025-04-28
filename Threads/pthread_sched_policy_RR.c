/* Scheduling Policy

✅ Round-Robin policy set with priority 10.
*/

#include <pthread.h>
#include <stdio.h>
#include <sched.h>

void* task(void* arg) {
    printf("Running with custom scheduling policy\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_attr_t attr;
    struct sched_param param;

    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_RR); // Round-robin
    param.sched_priority = 10;
    pthread_attr_setschedparam(&attr, &param);

    pthread_create(&tid, &attr, task, NULL);
    pthread_join(tid, NULL);

    return 0;
}