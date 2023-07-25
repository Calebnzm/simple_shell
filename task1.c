#include "shell.h"
#define BUFFER_SIZE 1024

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

/**
* custom_strlen - calculates length of string
* @str - the string
*
* Return: lenght of string(success)
*/
int custom_strlen(const char *str)
{
int len = 0;
while (str[len] != '\0')
{
len++;
}
return (len);
}


int custom_strcmp(const char *s1, const char *s2)
{
while (*s1 != '\0' && *s1 == *s2) {
s1++;
s2++;
}
return (*s1 - *s2);
}


/**
* executr_command - executes the command by user
* @command: the command entered
*
* Return: nothing(always)
*/
void execute_command(char *command_line)
{
pid_t pid;
int status, i;
char *envp[] = {NULL};
pid = fork();

if (custom_strcmp(command_line, "exit") == 0)
{
	printf("Exiting the shell.\n");
	exit(EXIT_SUCCESS);
}
    if (custom_strcmp(command_line, "env") == 0) {
        // Print the current environment
        extern char **environ;
        char **env = environ;
        while (*env != NULL) {
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
        for (int i = 0; command_line[i] != '\0'; i++) {
            if (command_line[i] == ' ') {
                arg_count++;
            }
        }

        char *argv[arg_count + 1]; // Additional 1 for NULL terminator
        int index = 0;
        int i = 0;
        while (command_line[i] != '\0') {
            // Skip leading spaces
            while (command_line[i] == ' ') {
                i++;
            }
            
            // Store the start of the current argument
            int arg_start = i;

            // Find the end of the current argument
            while (command_line[i] != ' ' && command_line[i] != '\0') {
                i++;
            }

            // Allocate memory for the current argument and copy it
            int arg_length = i - arg_start;
            argv[index] = (char *)malloc(arg_length + 1);
            if (argv[index] == NULL) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

            int j = 0;
            while (arg_start < i) {
                argv[index][j++] = command_line[arg_start++];
            }
            argv[index][j] = '\0';

            index++;
        }
        argv[arg_count] = NULL; // Set the last element to NULL to terminate the array

        if (execvp(argv[0], argv) == -1) {
            perror("Error executing command");
            for (int j = 0; j < arg_count; j++) {
                free(argv[j]); // Free the allocated memory for arguments
            }
            exit(EXIT_FAILURE);
        }
}
else
{
do {
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}



/**
* main - runs the shell
*
* Return: nothing
*/
int main(void)
{
char buffer[BUFFER_SIZE];
int read_bytes;
while (1)
{
display_prompt();
if ((read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) == -1)
{
	perror("Error reading input");
	continue;
}
if (read_bytes == 0)
{
	printf("\n");
	break;
}
buffer[read_bytes - 1] = '\0';
execute_command(buffer);
}
return (0);
}

