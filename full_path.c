#include "shell.h"

/**
 * execute_with_full_path - Execute a command with the full path and arguments
 * @full_path: The full path of the command to execute
 * @argv: An array of pointers to arguments, including the command itself
 *
 */
void execute_with_full_path(char *full_path, char **argv)
{
	extern char **environ;

	if (execve(full_path, argv, environ) == -1)
	{
		perror("Error executing command");
		for (int j = 0; argv[j] != NULL; j++)
		{
			free(argv[j]); /* Free the allocated memory for arguments */
		}
		free(argv);
		exit(EXIT_FAILURE);
	}
}
