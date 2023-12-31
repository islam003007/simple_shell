#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_ARG 128


int _putchar(char c);
char *str_concat(char *s1, char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strncmp(char *s1, char *s2, int n);
unsigned int _strlen(char *str);
char *_getenv(char *name, char **env);
void print_env(char **env);
ssize_t interface(char **buf, int *line);
void parser(char *args[], char *buf);
char *_strcat(char *dest, char *src);
void excute(char *args[], char **env, char **argv, int *line, int *exit_st);
int exit_sh(char *args[], int *exit_st, char *argv[], int line);
int _atoi(char *s);







#endif
