#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64
#define PROMPT "#cisfun$ "
#define DELIM " \t\r\n\a"

/* main.c */
int _putchar(char c);
int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, int n);
char **tokenizer(char *str, const char *delim);
char *read_line(void);
int execute(char **args);
void handle_signal(int signal);
char *_getenv(const char *name);
#endif /* MAIN_H */

