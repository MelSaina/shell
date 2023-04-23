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
extern char **environ;
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
int _main(void);
extern char **environ;

/* def */
char *_getenv(const char *name);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
void print_environment(void);

int run();
int run2();
int run3();
int run4();
int run5();
int main() {
    int result = 0;
    result += run();
    result += run2();
    result += run3();
    result += run4();
    result += run5();
    return result;
}
#endif /* MAIN_H */

