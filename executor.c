#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

// Split command line into arguments and return the array of arguments
char **split_command_line(char *command_line, int *arg_count)
{
    *arg_count = 1;
    for (int i = 0; command_line[i] != '\0'; i++)
    {
        if (command_line[i] == ' ')
        {
            (*arg_count)++;
        }
    }

    char **argv = (char **)malloc((*arg_count + 1) * sizeof(char *));
    if (argv == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(command_line, " ");
    int i = 0;
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
        strcpy(argv[i], token);
        token = strtok(NULL, " ");
        i++;
    }
    argv[i] = NULL; // Set the last element to NULL to terminate the array

    return argv;
}

// Execute the command with the provided full path
void execute_with_full_path(char *full_path, char **argv)
{
    extern char **environ; // Retrieve the current environment variables
    if (execve(full_path, argv, environ) == -1)
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

// Search for the full path of the command in the PATH environment variable
char *find_full_path(char *command)
{
    char *full_path = NULL;
    char *path = getenv("PATH");
    if (path != NULL)
    {
        char *token = strtok(path, ":");
        while (token != NULL)
        {
            int dir_length = strlen(token);
            int cmd_length = strlen(command);
            full_path = (char *)malloc((dir_length + cmd_length + 2) * sizeof(char));
            if (full_path == NULL)
            {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

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

    return full_path;
}

// Execute the command
void execute_command(char *command_line)
{
    int arg_count;
    char **argv = split_command_line(command_line, &arg_count);

    char *command = argv[0];
    int has_slash = 0;
    for (int i = 0; command[i] != '\0'; i++)
    {
        if (command[i] == '/')
        {
            has_slash = 1;
            break;
        }
    }

    if (has_slash)
    {
        execute_with_full_path(command, argv);
    }
    else
    {
        char *full_path = find_full_path(command);
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

        printf("Full path: %s\n", full_path);

        execute_with_full_path(full_path, argv);
    }

    for (int j = 0; argv[j] != NULL; j++)
    {
        free(argv[j]); // Free the allocated memory for arguments
    }
    free(argv);
}
