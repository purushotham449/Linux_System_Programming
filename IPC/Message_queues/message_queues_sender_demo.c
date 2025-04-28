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


Concept                             | Behavior
----------------------------------------------------------------------------------------------

Multiple same-type messages         | Allowed
Order                               | FIFO (First-In, First-Out)
Delay between sends                 | No problem; order remains correct
Receiving                           | Pick first matching type available

Sender sends 3 messages:

    "Normal Update" (type = 10)
    "Critical Alert" (type = 100)
    "Minor Notification" (type = 1)

Receiver waits first for high-priority (type = 100) then handles others
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

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Prepare a message
    message.mtype = 2;  // Example: "STOP" command (type 2)
    strcpy(message.mtext, "STOP");

    // Send message
    msgsnd(msgid, &message, sizeof(message.mtext), 0);

    printf("Command Sent: %s (Type: %ld)\n", message.mtext, message.mtype);

    return 0;
}