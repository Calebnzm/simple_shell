#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
	const char prompt[] = "#cisfun$ ";
	write(STDOUT_FILENO, prompt, custom_strlen(prompt));
}

/**
 * main - Entry point for the simple shell program.
 * @argc: The number of command-line arguments.
 * @argv: An array containing the command-line arguments.
 * @env: An array containing the environment variables.
 *
 * Return: The exit status of the shell program.
 */
int main(int argc, char *argv[], char *env[])
{
	char buffer[BUFFER_SIZE];
	int read_bytes;
	bool interactive = isatty(STDIN_FILENO);

	while (1)
	{
		/* Display the shell prompt to the user (in interactive mode) */
		if (interactive)
			display_prompt();

		/* Read input from the user or from a file (interactive/non-interactive) */
		if ((read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) == -1)
		{
			perror("Error reading input");
			continue;
		}

		/* Check for end-of-file condition (Ctrl+D) */
		if (read_bytes == 0)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove the trailing newline character (if present) in interactive mode */
		if (interactive && buffer[read_bytes - 1] == '\n')
		{
			buffer[read_bytes - 1] = '\0';
			read_bytes--;
		}

		if (custom_strlen(buffer) == 0)
		{
			/* Empty input, display the prompt again (in interactive mode) */
			if (interactive)
				continue;
			else
				break; /* Exit non-interactive mode after reading commands from a file */
		}

		execute_command(buffer, env);
	}

	return (0);
}
