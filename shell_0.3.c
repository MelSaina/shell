#include "main.h"

int main3(void)
{
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int status, i;
    char *token;

    char* system_path = getenv("PATH");
    char* updated_path = malloc(strlen(system_path) + strlen(getenv("PATH")) + 2);

    strcpy(updated_path, system_path);
    strcat(updated_path, ":");
    strcat(updated_path, getenv("PATH"));

    setenv("PATH", updated_path, 1);

    free(updated_path);

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

        if (access(args[0], X_OK) == 0)
        {
            if (fork() == 0)
            {
                if (execvp(args[0], args) == -1)
                {
                    perror(args[0]);
                    exit(0);
                }
            }
            else
            {
                wait(&status);
            }
        }
        else
        {
            char *path = getenv("PATH");
            char *dir = strtok(path, ":");
            while (dir != NULL)
            {
                char command[MAX_CMD_LEN];
                snprintf(command, sizeof(command), "%s/%s", dir, args[0]);
                if (access(command, X_OK) == 0)
                {
                    args[0] = command;
                    if (fork() == 0)
                    {
                        if (execvp(args[0], args) == -1)
                        {
                            perror(args[0]);
                            exit(0);
                        }
                    }
                    else
                    {
                        wait(&status);
                    }
                    break;
                }
                dir = strtok(NULL, ":");
            }
            if (dir == NULL)
            {
                fprintf(stderr, "%s: command not found\n", args[0]);
            }
        }
    }
    return (0);
}
int run3() {
    return main3();
}
