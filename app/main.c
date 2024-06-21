#include <stdio.h>

#include "shell.h"
#include "thread.h"

#include "sender.h"
#include "receiver.h"
#include "measurements.h"

char sender_stack[THREAD_STACKSIZE_MAIN];
char receiver_stack[THREAD_STACKSIZE_MAIN];


// this is the IP address of the receiver
char const *IP_STRING = IP_ADDR;

int send_cmd(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: send <destination>\n");
        return 1;
    }

    thread_create(sender_stack, sizeof(sender_stack), THREAD_PRIORITY_MAIN - 1,
                   THREAD_CREATE_STACKTEST, sender_loop, argv[1], "sender");
    (void) argv;
    return 0;
}

int receive_cmd(int argc, char **argv) {
    if (argc != 1) {
        printf("Usage: receive\n");
        return 1;
    }

    thread_create(receiver_stack, sizeof(receiver_stack), THREAD_PRIORITY_MAIN - 1,
                   THREAD_CREATE_STACKTEST, receiver_loop, NULL, "receiver");

    (void) argv;
    return 0;

}

SHELL_COMMAND(send, "Starts the measurement and send loop.", send_cmd);
SHELL_COMMAND(receive, "Receives all incoming packages and prints them.", receive_cmd);
int main(void)
{
    #ifdef SENDER
        send_cmd(2, (char *[]){"send", IP_STRING});
    #elif defined(RECEIVER)
        receive_cmd(1, (char *[]){"receive"});
    #else
        /* buffer to read commands */
        char line_buf[SHELL_DEFAULT_BUFSIZE];

        /* run the shell, this will block the thread waiting for incoming commands */
        shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    #endif

    return 0;
}