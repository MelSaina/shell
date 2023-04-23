#include "main.h"

extern char **environ;
int main4(void)
{
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int status, i;
    char *token;
    char *path, *path_token, *path_copy;
    char full_path[MAX_CMD_LEN];
	char *new_path = "/usr/bin:/usr/local/bin"; /* add the directories containing the commands you want to use*/
	setenv("PATH", new_path, 1);
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
char *_getenv(const char *name)
{
        int i, len;
        len = _strlen(name);
        for (i = 0; environ[i] != NULL; i++)
        {
                if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
                {
                        return (environ[i] + len + 1);
                }
        }
        return (NULL);
}
char *_strcat(char *dest, char *src)
{
    int dest_len = _strlen(dest);
    int i;

    for (i = 0; src[i] != '\0'; i++)
    {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';

    return (dest);
}

int _strcmp(char *s1, char *s2)
{
    int i;

    for (i = 0; s1[i] == s2[i]; i++)
    {
        if (s1[i] == '\0')
        {
            return (0);
        }
    }

    return (s1[i] - s2[i]);
}
int _strncmp(const char*s1, const char *s2, int n)
{
    int i;

    for (i = 0; i < n && s1[i] == s2[i]; i++)
    {
        if (s1[i] == '\0')
        {
            return (0);
        }
    }

    if (i == n)
    {
        return (0);
    }

    return (s1[i] - s2[i]);
}

char *_strcpy(char *dest, char *src)
{
    int i = 0;

    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';

    return (dest);
}

int _strlen(const char *s)
{
    int len = 0;

    while (s[len] != '\0')
    {
        len++;
    }

    return (len);
}

int _main(void)
{
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int status, i;
    char *token;
    char *path, *path_token, *path_copy;
    char full_path[MAX_CMD_LEN];
    int cmd_exists = 0;

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
                    cmd_exists = 1;

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

            if (!cmd_exists)
            {
                printf("%s: command not found\n", args[0]);
            }

            free(path_copy);
        }
    }

    return (0);
}
