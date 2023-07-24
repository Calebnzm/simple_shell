#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <dirent.h>

#define MAX_COMMAND_LENGTH 100
#define BUFFER_SIZE 1024

int custom_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char *find_command_path(char *command, char **env) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *token = strtok(path_copy, ":");

    while (token != NULL) {
        char full_path[MAX_COMMAND_LENGTH];
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);

        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return strdup(full_path);
        }

        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL; // Command not found or not executable
}

void execute_command(char *command_with_args, char **env) {
    char *token;
    char *args[MAX_COMMAND_LENGTH];
    int i = 0;

    // Tokenize the command with arguments
    token = strtok(command_with_args, " ");
    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Null-terminate the argument list

    if (strcmp(args[0], "exit") == 0) {
        // Exit the shell if the command is "exit"
        exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "env") == 0) {
        // Print the environment variables if the command is "env"
        char **env_ptr = env;
        while (*env_ptr) {
            printf("%s\n", *env_ptr);
            env_ptr++;
        }
    } else if (strcmp(args[0], "/bin/ls") == 0) {
        // List files in the current directory if the command is "/bin/ls"
        DIR *dir;
        struct dirent *entry;

        dir = opendir(".");
        if (dir == NULL) {
            perror("Unable to open directory");
            return;
        }

        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }

        closedir(dir);
    } else {
        // Find the full path of the command
        char *full_path = find_command_path(args[0], env);
        if (full_path != NULL) {
            pid_t pid = fork();

            if (pid < 0) {
                perror("Fork failed");
                free(full_path);
                return;
            } else if (pid == 0) {
                // Child process
                if (execve(full_path, args, env) == -1) {
                    perror("Execution error");
                    free(full_path);
                    exit(EXIT_FAILURE);
                }
            } else {
                // Parent process
                int status;
                waitpid(pid, &status, 0);
            }

            free(full_path);
        } else {
            printf("Command not found: %s\n", args[0]);
        }
    }
}

void display_prompt() {
    const char prompt[] = "Shell> ";
    write(STDOUT_FILENO, prompt, custom_strlen(prompt));
}

int main(int argc, char *argv[], char *env[]) {
    char buffer[BUFFER_SIZE];
    int read_bytes;
    bool interactive = isatty(STDIN_FILENO);

    while (1) {
        // Display the shell prompt to the user (in interactive mode)
        if (interactive)
            display_prompt();

        // Read input from the user or from a file (interactive/non-interactive)
        if ((read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) == -1) {
            perror("Error reading input");
            continue;
        }

        // Check for end-of-file condition (Ctrl+D)
        if (read_bytes == 0) {
            if (interactive)
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        // Remove the trailing newline character (if present) in interactive mode
        if (interactive && buffer[read_bytes - 1] == '\n') {
            buffer[read_bytes - 1] = '\0';
            read_bytes--;
        }

        if (custom_strlen(buffer) == 0) {
            // Empty input, display the prompt again (in interactive mode)
            if (interactive)
                continue;
            else
                break; // Exit non-interactive mode after reading commands from a file
        }

        execute_command(buffer, env);
    }

    return 0;
}
