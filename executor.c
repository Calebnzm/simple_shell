#include "shell.h"

/**
 * handle_builtin_commands - Handle built-in commands
 * @command_line: The command line
 *
 * Return: 1 if the command is a built-in command, otherwise 0
 */
int handle_builtin_commands(char *command_line)
{
	if (custom_strcmp(command_line, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}

	if (custom_strcmp(command_line, "env") == 0)
	{
		char **env = environ;
		int fd = STDOUT_FILENO;

		while (*env != NULL)
		{
			write(fd, *env, custom_strlen(*env));
			write(fd, "\n", 1);
			env++;
		}
		return (1);
	}

	return (0);
}

/**
 * split_command_line - Split the command line into arguments
 * @command_line: The command line
 * @arg_count: Pointer to the number of arguments
 *
 * Return: An array of strings representing the arguments
 */
char **split_command_line(char *command_line, int *arg_count)
{
	int i, j, arg_length;
	char *token, **argv;

	*arg_count = 1;
	for (i = 0; command_line[i] != '\0'; i++)
	{
		if (command_line[i] == ' ')
			(*arg_count)++;
	}
	argv = (char **)malloc((*arg_count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(command_line, " ");
	i = 0;
	while (token != NULL)
	{
		arg_length = custom_strlen(token);
		argv[i] = malloc((arg_length + 1) * sizeof(char));
		if (argv[i] == NULL)
		{
			perror("Memory allocation failed");
			for (j = 0; j < i; j++)
				free(argv[j]);
			free(argv);
			exit(EXIT_FAILURE);
		}
		for (j = 0; token[j] != '\0'; j++)
			argv[i][j] = token[j];
		argv[i][j] = '\0';
		token = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * execute_with_full_path - Execute a command with its full path
 * @full_path: The full path of the executable
 * @argv: The arguments of the command
 */
void execute_with_full_path(char *full_path, char **argv)
{
	int j;

	if (execve(full_path, argv, environ) == -1)
	{
		perror("Error executing command");
		for (j = 0; argv[j] != NULL; j++)
			free(argv[j]);
		free(argv);
		exit(EXIT_FAILURE);
	}
}

/**
 * find_full_path - Find the full path of an executable
 * @command: The name of the command
 *
 * Return: The full path of the executable, or NULL if not found
 */
char *find_full_path(char *command)
{
	char *full_path, *token, *path;
	int j, dir_length, k, cmd_length;

	full_path = NULL;
	path = NULL;
	for (j = 0; environ[j] != NULL; j++)
	{
		if (custom_strncmp(environ[j], "PATH=", 5) == 0)
		{
			path = environ[j] + 5;
			break;
		}
	}
	if (path != NULL)
	{
		token = strtok(path, ":");
		while (token != NULL)
		{
			dir_length = custom_strlen(token);
			cmd_length = custom_strlen(command);
			full_path = malloc((dir_length + cmd_length + 2) * sizeof(char));
			if (full_path == NULL)
			{
				perror("Memory allocation failed");
				exit(EXIT_FAILURE);
			}
			for (j = 0; token[j] != '\0'; j++)
			{
				full_path[j] = token[j];
			}
				full_path[j++] = '/';
			for (k = 0; command[k] != '\0'; k++)
			{
				full_path[j++] = command[k];
			}
				full_path[j] = '\0';
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
			token = strtok(NULL, ":");
		}
	}
	return (NULL);
}

/**
 * execute_command - Execute a command
 * @command_line: The command line
 */
void execute_command(char *command_line)
{
	char **argv, *command, *full_path;
	int status, i, arg_count, has_slash;

	pid = fork();
	if (handle_builtin_commands(command_line))
		return;
	if (pid < 0)
	{
		perror("Forking failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
	argv = split_command_line(command_line, &arg_count);
	command = argv[0];
	has_slash = 0;
	for (i = 0; command[i] != '\0'; i++)
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
		full_path = find_full_path(command);
		saver(full_path, argv, command);
		execute_with_full_path(full_path, argv);
		free(full_path);
	}
	freer(argv);
	}
	else
		wait(&status);
}
