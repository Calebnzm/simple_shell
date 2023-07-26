#include "shell.h"

/**
 * split_command_line - Split command line into arguments 
 * @command_line: The input command line string
 * @arg_count: A pointer to an integer to store the number of arguments
 *
 * Return: An array of strings containing the arguments
 */
char **split_command_line(char *command_line, int *arg_count)
{
	/* Count the number of arguments in the command line */
	*arg_count = 1;

	for (int i = 0; command_line[i] != '\0'; i++)
	{
		if (command_line[i] == ' ')
		{
			(*arg_count)++;
		}
	}
	/* Allocate memory for the array of strings to hold the arguments */
	char **argv = (char **)malloc((*arg_count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	/* Tokenize the command line and store each argument in the array */
	char *token = strtok(command_line, " ");
	int i = 0;
	while (token != NULL)
	{
		int arg_length = strlen(token);

		/* Allocate memory for each argument */
		argv[i] = (char *)malloc((arg_length + 1) * sizeof(char));
		if (argv[i] == NULL)
		{
			perror("Memory allocation failed");
			/* Free allocated memory for previous arguments */
			for (int j = 0; j < i; j++)
			{
				free(argv[j]);
			}
			free(argv);
			exit(EXIT_FAILURE);
		}
		/* Copy the argument into the array */
		strcpy(argv[i], token);
		/* Get the next argument */
		token = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL; /* Set the last element to NULL to terminate the array */
	return (argv);
}
