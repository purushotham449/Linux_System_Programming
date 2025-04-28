/* 
Send Structured Messages
----------------------------------------------------------------------------------------------

    Each message has:

        a type (a positive number)
        and a payload (actual data you want to send).
    
Send Multiple Messages
----------------------------------------------------------------------------------------------

    A message queue can hold many messages at the same time.
    You can send many before the receiver picks them up.
    Linux kernel internally manages the queue.

✅ Example:
Process A sends 5 different messages into the same queue. Process B reads one by one later.

Priority with Message Types
----------------------------------------------------------------------------------------------

✅ Example:

    Message Type 1: Low priority
    Message Type 10: High priority

Command Queues
----------------------------------------------------------------------------------------------

✅ Example:

    Type 1 = Start
    Type 2 = Stop
    Type 3 = Restart

Point                               | Details
----------------------------------------------------------------------------------------------
Message type must be > 0            | Always positive number (long mtype)
Send/Receive different types        | Use msgsnd() and msgrcv() carefully
ftok()                              | Creates a common key between sender and receiver
msgctl() with IPC_RMID              | Removes the message queue after use

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;
    struct msgbuf message;

    // Create unique key
    key = ftok("progfile", 65);

    // Access the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Receive any message with type 2 (STOP command)
    msgrcv(msgid, &message, sizeof(message.mtext), 2, 0);

    printf("Command Received: %s (Type: %ld)\n", message.mtext, message.mtype);

    // Destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}