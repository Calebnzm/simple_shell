#include "shell.h"

/**
* display_prompt -  Function to display the shell prompt
*
* Return: nothing
*/
void display_prompt(void)
{
	char prompt[] = "$ ";
	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}
