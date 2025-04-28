/* File Descriptor Sharing between Threads

✅ Threads share file descriptors because they share process resources.

✅ Both threads write to the same file!

*/

#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int fd; // Shared file descriptor

void* writeToFile(void* arg) {
    const char* message = "Hello from thread\n";
    printf("Thread %lu message written!!!!!!!!!\n", pthread_self());
    write(fd, message, 18);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    fd = open("thread_file.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);

    pthread_create(&t1, NULL, writeToFile, NULL);
    pthread_create(&t2, NULL, writeToFile, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    close(fd);
    printf("Main: File written.\n");
    return 0;
}