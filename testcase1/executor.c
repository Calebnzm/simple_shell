#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <dirent.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100

/**
 * execute_command - Execute the provided command.
 * @command_with_args: The command with arguments to execute.
 * @env: The environment variables.
 *
 * Return: None.
 */
void execute_command(char *command_with_args, char **env)
{
	char *token;
	char *args[MAX_COMMAND_LENGTH];
	int i = 0;

	/* Tokenize the command with arguments */
	token = strtok(command_with_args, " ");
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL; /* Null-terminate the argument list */

	if (strcmp(args[0], "exit") == 0)
	{
		/* Exit the shell if the command is "exit" */
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		/* Print the environment variables if the command is "env" */
		char **env_ptr = env;
		while (*env_ptr)
		{
			printf("%s\n", *env_ptr);
			env_ptr++;
		}
	}
	else if (strcmp(args[0], "/bin/ls") == 0)
	{
		/* List files in the current directory if the command is "/bin/ls" */
		DIR *dir;
		struct dirent *entry;

		dir = opendir(".");
		if (dir == NULL)
		{
			perror("Unable to open directory");
			return;
		}

		while ((entry = readdir(dir)) != NULL)
		{
			printf("%s\n", entry->d_name);
		}

		closedir(dir);
	}
	else
	{
		/* Find the full path of the command */
		char *full_path = find_command_path(args[0], env);
		if (full_path != NULL)
		{
			pid_t pid = fork();

			if (pid < 0)
			{
				perror("Fork failed");
				free(full_path);
				return;
			}
			else if (pid == 0)
			{
				/* Child process */
				if (execve(full_path, args, env) == -1)
				{
					perror("Execution error");
					free(full_path);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				/* Parent process */
				int status;
				waitpid(pid, &status, 0);
			}

			free(full_path);
		}
		else
		{
			printf("Command not found: %s\n", args[0]);
		}
	}
}
