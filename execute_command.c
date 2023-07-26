#include "shell.h"
/**
 * execute_command - Executes a command based on the given command line.
 *
 * @command_line: The command line containing the command and its arguments.
 */
void execute_command(char *command_line)
{
	/*Split the command line into arguments*/
	int arg_count;
	char **argv = split_command_line(command_line, &arg_count);
	char *command = argv[0];
	int has_slash = 0;
	char *full_path = find_full_path(command);

	for (int i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
		{
			has_slash = 1;
			break;
		}
	}
	if (has_slash)
		execute_with_full_path(command, argv);
	else
	{
		if (full_path == NULL)
		{
			/* Executable not found */
			fprintf(stderr, "Error: Command not found: %s\n", command);
			for (int j = 0; argv[j] != NULL; j++)
			{
				free(argv[j]);
			}
			free(argv);
			exit(EXIT_FAILURE);
		}
		printf("Full path: %s\n", full_path);
		execute_with_full_path(full_path, argv);
		free(full_path); /* Free the allocated memory for the full path */
	}
	/* Free the allocated memory for arguments */
	for (int j = 0; argv[j] != NULL; j++)
	{
		free(argv[j]);
	}
	free(argv);
}
