#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

void execute_command(char *command_line)
{
    pid_t pid;
    int status, i;

    pid = fork();

    if (custom_strcmp(command_line, "exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }

    if (custom_strcmp(command_line, "env") == 0)
    {
        // Print the current environment
        extern char **environ;
        char **env = environ;
        while (*env != NULL)
        {
            printf("%s\n", *env);
            env++;
        }
        return;
    }

    if (pid < 0)
    {
        perror("Forking failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Count the number of arguments by counting spaces
        int arg_count = 1;
        for (i = 0; command_line[i] != '\0'; i++)
        {
            if (command_line[i] == ' ')
            {
                arg_count++;
            }
        }

        char **argv = (char **)malloc((arg_count + 1) * sizeof(char *));
        if (argv == NULL)
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        // Tokenize the command line into arguments
        char *token = strtok(command_line, " ");
        i = 0;
        while (token != NULL)
        {
            int arg_length = strlen(token);
            argv[i] = (char *)malloc((arg_length + 1) * sizeof(char));
            if (argv[i] == NULL)
            {
                perror("Memory allocation failed");
                for (int j = 0; j < i; j++)
                {
                    free(argv[j]);
                }
                free(argv);
                exit(EXIT_FAILURE);
            }

            // Manually copy characters from token to argv[i]
            int j;
            for (j = 0; token[j] != '\0'; j++)
            {
                argv[i][j] = token[j];
            }
            argv[i][j] = '\0';

            token = strtok(NULL, " ");
            i++;
        }
        argv[i] = NULL; // Set the last element to NULL to terminate the array

        // Execute the command using execve with the full path
        char *command = argv[0];

        // Check if the command contains '/'
        int has_slash = 0;
        for (i = 0; command[i] != '\0'; i++)
        {
            if (command[i] == '/')
            {
                has_slash = 1;
                break;
            }
        }

        if (has_slash)
        {
            extern char **environ; // Retrieve the current environment variables
            if (execve(command, argv, environ) == -1)
            {
                perror("Error executing command");
                for (int j = 0; argv[j] != NULL; j++)
                {
                    free(argv[j]); // Free the allocated memory for arguments
                }
                free(argv);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Search for the executable in the PATH
            char *full_path = NULL;
            char *path = getenv("PATH");
            if (path != NULL)
            {
                char *token = strtok(path, ":");
                while (token != NULL)
                {
                    // Construct the full path by concatenating the token (directory) with the command
                    int dir_length = strlen(token);
                    int cmd_length = strlen(command);
                    full_path = (char *)malloc((dir_length + cmd_length + 2) * sizeof(char));
                    if (full_path == NULL)
                    {
                        perror("Memory allocation failed");
                        for (int j = 0; argv[j] != NULL; j++)
                        {
                            free(argv[j]);
                        }
                        free(argv);
                        exit(EXIT_FAILURE);
                    }

                    // Manually copy characters from token to full_path
                    int j;
                    for (j = 0; token[j] != '\0'; j++)
                    {
                        full_path[j] = token[j];
                    }
                    full_path[j] = '/';
                    j++;

                    for (int k = 0; command[k] != '\0'; k++, j++)
                    {
                        full_path[j] = command[k];
                    }
                    full_path[j] = '\0';

                    if (access(full_path, X_OK) == 0)
                    {
                        // Found the executable, break the loop
                        break;
                    }

                    free(full_path);
                    full_path = NULL;
                    token = strtok(NULL, ":");
                }
            }

            if (full_path == NULL)
            {
                // Executable not found
                fprintf(stderr, "Error: Command not found: %s\n", command);
                for (int j = 0; argv[j] != NULL; j++)
                {
                    free(argv[j]);
                }
                free(argv);
                exit(EXIT_FAILURE);
            }

            extern char **environ; // Retrieve the current environment variables
            if (execve(full_path, argv, environ) == -1)
            {
                perror("Error executing command");
                free(full_path);
                for (int j = 0; argv[j] != NULL; j++)
                {
                    free(argv[j]); // Free the allocated memory for arguments
                }
                free(argv);
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
