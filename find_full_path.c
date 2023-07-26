#include "shell.h"

/**
 * find_full_path - Find the full path of an executable command
 *
 * @command: The command whose full path needs to be found.
 *
 * Return: A pointer to the full path of the command if found, NULL otherwise.
 */
char *find_full_path(char *command)
{
	char *full_path = NULL;
	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	int dir_length = strlen(token);
	int cmd_length = strlen(command);
	int j;

	if (path != NULL)
	{
		while (token != NULL)
		{
			full_path = (char *)malloc((dir_length + cmd_length + 2) * sizeof(char));
			if (full_path == NULL)
			{
				perror("Memory allocation failed");
				exit(EXIT_FAILURE);
			}
			for (j = 0; token[j] != '\0'; j++)
			{
				full_path[j] = token[j];
			}
			full_path[j] = '/';
			j++;
			for (int k = 0; command[k] != '\0'; k++, j++)
			{
				full_path[j] = command[k];
			}
			full_path[j] = '\0';
			if (access(full_path, X_OK) == 0)
			{
				break;
			}
			free(full_path);
			full_path = NULL;
			token = strtok(NULL, ":");
		}
	}
	return (full_path);
}
