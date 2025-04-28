/* IPC - Message Queues

Message Queues are a more structured form of IPC, allowing processes to send and receive messages 
in a queue-like fashion. They provide message-based communication, where messages can have priorities.

Example: One process sends a message to a queue, and another process receives the message

Explanation:

    msgget: Create or access a message queue.
    msgsnd: Send a message to the queue.
    msgrcv: Receive a message from the queue.
    msgctl: Control operations on the message queue, such as removing it
    
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Define message structure
struct msgbuf {
    long mtype;       // message type
    char mtext[100];  // message content
};

int main() {
    key_t key = ftok("msgqueue", 65);  // Generate a unique key
    int msgid = msgget(key, 0666 | IPC_CREAT);  // Create a message queue

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    struct msgbuf message;
    message.mtype = 1;  // Message type
    strcpy(message.mtext, "Hello, Message Queue!");

    // Send message
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Message sent: %s\n", message.mtext);

    // Receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Message received: %s\n", message.mtext);

    // Remove message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}