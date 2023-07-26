#include "shell.h"

/**
* writeerror - displays error
* @command: the command to be printed
*
* Return - nothing
*/
void writeerror(char *command)
{
	char *msg = "Error: Command not found: ";

	write(STDERR_FILENO, msg, custom_strlen(msg));
	write(STDERR_FILENO, command, custom_strlen(command));
	write(STDERR_FILENO, "\n", 1);
}

/**
* freer - frees the argv
* @argv: the vector to be freed
*
* Return: nothing
*/
void freer(char **argv)
{
	int j;

	for (j = 0; argv[j] != NULL; j++)
	{
		free(argv[j]);
	}
	free(argv);
}


/**
* saver - checks if full_path is NULL
* @command: the command to be printed
* @argv: the vector to be freed
* @full_path: the path
*
* Return: Nothing
*/
void saver(char *full_path, char **argv, char *command)
{
	if (full_path == NULL)
	{
		writeerror(command);
		freer(argv);
		exit(EXIT_FAILURE);
	}
}
