#include "main.h"

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the variable.
 *
 * Return: The value of the variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
    char **env = environ;
    size_t namelen = strlen(name);

    while (*env)
    {
        if (strncmp(name, *env, namelen) == 0 && (*env)[namelen] == '=')
            return (*env + namelen + 1);

        env++;
    }

    return NULL;
}
