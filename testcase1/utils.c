#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "shell.h"

/**
 * custom_strlen - Calculate the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
int custom_strlen(const char *str)
{
	int length = 0;

	while (str[length] != '\0')
		length++;

	return (length);
}

/**
 * is_valid_command - Check if a command is a valid executable.
 * @command: The command to check.
 * @env: The environment variables.
 *
 * Return: (1) if the command is valid, (0) otherwise.
 */
int is_valid_command(char *command, char **env)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");

	while (token != NULL)
	{
		char full_path[MAX_COMMAND_LENGTH];
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (1); /* Command found and executable */
		}

		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (0); /* Command not found or not executable */
}

/**
 * find_command_path - Find the full path of a command in the PATH.
 * @command: The command to find.
 * @env: The environment variables.
 *
 * Return: The full path of the command, or NULL if not found.
 */
char *find_command_path(char *command, char **env)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");

	while (token != NULL)
	{
		char full_path[MAX_COMMAND_LENGTH];
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}

		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL); /* Command not found or not executable */
}
