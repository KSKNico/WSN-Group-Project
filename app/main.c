#include <stdio.h>

#include "shell.h"
#include "thread.h"

#include "sender.h"
#include "receiver.h"
#include "measurements.h"

void print_package(void) {
}

int send_cmd(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: send <destination>\n");
        return 1;
    }
    (void) argv;
    return 0;
}

int receive_cmd(int argc, char **argv) {
    if (argc != 1) {
        printf("Usage: receive\n");
        return 1;
    }

    (void) argv;
    return 0;

}

SHELL_COMMAND(send, "Starts the measurement and send loop.", send_cmd);
SHELL_COMMAND(receive, "Receives all incoming packages and prints them.", receive_cmd);
int main(void)
{
    /* buffer to read commands */
    char line_buf[SHELL_DEFAULT_BUFSIZE];

    /* run the shell, this will block the thread waiting for incoming commands */
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}