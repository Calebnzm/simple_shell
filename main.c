#include "shell.h"

/**
 * is_interactive_shell - Check if the shell is running in interactive mode.
 *
 * Return: true if running in interactive mode, false otherwise.
 */
bool is_interactive_shell(void)
{
	return (isatty(STDIN_FILENO) != 0);
}

/**
 * main - Entry point for the shell program.
 *
 * Description: This function initializes the shell and enters a loop
 * where it continuously displays a prompt, reads input from the user,
 * and executes the entered command.
 *
 * Return: Always returns 0 to indicate successful program termination.
 */
int main(void)
{
	/* Declare variables */
	char buffer[BUFFER_SIZE]; /* Buffer to store user input */
	bool interactive_mode = is_interactive_shell();
	int read_bytes; /* Number of bytes read from user input */

	/* Start the main loop */
	while (1)
	{
		if (interactive_mode)
			display_prompt(); /* Display the shell prompt */

		/* Read input from the user and handle errors */
		read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			perror("Error reading input");
			continue; /* Continue to the next iteration of the loop */
		}

		/* Check for end of input (Ctrl+D) and break the loop */
		if (read_bytes == 0)
		{
			write(STDOUT_FILENO, "\n", 1); /* Print a new line using write */
			break; /* Exit the loop */
		}

		buffer[read_bytes - 1] = '\0'; /* Null-terminate the input string */
		execute_command(buffer); /* Execute the command entered by the user */
	}
	return (0); /* Indicate successful program termination */
}
