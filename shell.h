#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stddef.h>
#define MAX_COMMAND_LENGTH 100
#define BUFFER_SIZE 1024

int custom_strncmp(const char *s1, const char *s2, size_t n);
void saver(char *full_path, char **argv, char *command);
pid_t pid;
void writeerror(char *command);
void freer(char **argv);
extern char **environ;
void display_prompt(void);
char **split_command_line(char *command_line, int *arg_count);
void execute_with_full_path(char *full_path, char **argv);
char *find_full_path(char *command);
void execute_command(char *command_line);
int custom_strlen(const char *str);
int custom_strcmp(const char *s1, const char *s2);
int main(void);

#endif /* KELVIN && CALEB */
