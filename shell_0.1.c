#include "main.h"

int main1(void)
{
    char cmd[MAX_CMD_LEN];
    char *args[] = {NULL, NULL};
    int status;

    while (1)
    {
        printf(PROMPT);
        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
        {
            printf("\n");
            exit(0);
        }
        cmd[strlen(cmd) - 1] = '\0';
        args[0] = cmd;
        if (fork() == 0)
        {
            if (execve(args[0], args, NULL) == -1)
            {
                perror(args[0]);
            }
            exit(0);
        }
        else
        {
            wait(&status);
        }
    }
    return (0);
}
int run() {
    return main1();
}
