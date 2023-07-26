#include "shell.h"

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
	int read_bytes; /* Number of bytes read from user input */

	/* Start the main loop */
	while (1)
	{
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
			printf("\n"); /* Print a new line to keep the output clean */
			break; /* Exit the loop */
		}

		buffer[read_bytes - 1] = '\0'; /* Null-terminate the input string */
		execute_command(buffer); /* Execute the command entered by the user */
	}

	return (0); /* Indicate successful program termination */
}
