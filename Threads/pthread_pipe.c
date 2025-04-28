/* Communication Between Threads using Pipe

✅ You can set up a pipe inside one process and share between threads.
✅ One thread writes to pipe, another thread reads it!

*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int pipefd[2];

void* writePipe(void* arg) {
    const char* msg = "Hello thread pipe!!!!!!!!!!!\n";
    printf("Thread %lu message written!!!!!!!!!\n", pthread_self());
    write(pipefd[1], msg, 30);
    return NULL;
}

void* readPipe(void* arg) {
    char buf[100];
    read(pipefd[0], buf, sizeof(buf));
    printf("Thread %lu message read!!!!!!!!!\n", pthread_self());
    printf("Thread: Read from pipe: %s\n", buf);
    return NULL;
}

int main() {
    pthread_t writer, reader;
    pipe(pipefd);

    pthread_create(&writer, NULL, writePipe, NULL);
    pthread_create(&reader, NULL, readPipe, NULL);

    pthread_join(writer, NULL);
    pthread_join(reader, NULL);

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}