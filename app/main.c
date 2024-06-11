#include "shell.h"

int main(void)
{
    /* buffer to read commands */
    char line_buf[SHELL_DEFAULT_BUFSIZE];

    /* run the shell, this will block the thread waiting for incoming commands */
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}