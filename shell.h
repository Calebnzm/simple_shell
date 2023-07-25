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

void display_prompt();
void execute_command(char *command_line);
int custom_strlen(const char *str);
int custom_strcmp(const char *s1, const char *s2);
int main(void);

#endif /* KELVIN && CALEB */
