#include "shell.h"

/**
 * display_prompt - Function to display the shell prompt
 *
 * This function is responsible for displaying the shell prompt, which is
 * typically represented by "$ " in most shells.
 *
 * Return: Nothing
 */
void display_prompt(void)
{
	/* The prompt to be displayed */
	char prompt[] = "#cisfun$ ";

	/* Write the prompt to the standard output */
	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}
