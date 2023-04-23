#include "main.h"
#include <stdlib.h>

int main(void)
{
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int status, i;
    char *token;
    char *path, *path_token, *path_copy;
    char full_path[MAX_CMD_LEN];

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

        if (args[0] != NULL)
        {
            /* Check for built-in commands*/
            if (strcmp(args[0], "exit") == 0)
            {
                exit(0);
            }

            path = _getenv("PATH");
            path_copy = strdup(path);
            path_token = strtok(path_copy, DELIM);
            while (path_token != NULL)
            {
                _strcpy(full_path, path_token);
                _strcat(full_path, "/");
                _strcat(full_path, args[0]);

                if (access(full_path, F_OK) == 0)
                {
                    if (fork() == 0)
                    {
                        execve(full_path, args, NULL);
                    }
                    else
                    {
                        wait(&status);
                        break;
                    }
                }

                path_token = strtok(NULL, DELIM);
            }

            if (path_token == NULL)
            {
                printf("%s: command not found\n", args[0]);
            }

            free(path_copy);
        }
    }

    return (0);
}

