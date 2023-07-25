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

#define MAX_COMMAND_LENGTH 100
#define BUFFER_SIZE 1024

int add();
void display_prompt();
void execute_command(char *command_with_args, char **env);
char *find_command_path(char *command, char **env);
int custom_strlen(const char *str);
int is_valid_command(char *command, char **env);

#endif /* KELVIN && CALEB */
