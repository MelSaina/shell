#include "main.h"

int main2(void)
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
        cmd[strcspn(cmd, "\n")] = '\0';
 	i = 0;
        token = strtok(cmd, DELIM);
        while (token != NULL && i < MAX_ARGS-1)
	{
            args[i] = token;
            i++;
            token = strtok(NULL, DELIM);
        }
        args[i] = NULL;
        if (i > 0 && strcmp(args[0], "exit") == 0)
        {
            exit(0);
        }
        if (fork() == 0)
        {
            if (execvp(args[0], args) == -1)
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
int run2() {
    return main2();
}
