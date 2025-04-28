/* pthread RWLock (Read-Write Lock) - read lock */

#include <pthread.h>
#include <stdio.h>

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* reader(void* arg) {
    pthread_rwlock_rdlock(&rwlock);
    printf("Reader thread reading data\n");
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, reader, NULL);
    pthread_join(tid, NULL);
    return 0;
}