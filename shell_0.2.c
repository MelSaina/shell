#include "main.h"

int main(void)
{
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int status, i;
    char *token;

    while (1)
    {
        printf(PROMPT);
        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
        {
            printf("\n");
            exit(0);
        }
        cmd[strlen(cmd) - 1] = '\0';
        i = 0;
        token = strtok(cmd, DELIM);
        while (token != NULL)
        {
            args[i] = token;
            i++;
            token = strtok(NULL, DELIM);
        }
        args[i] = NULL;
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
