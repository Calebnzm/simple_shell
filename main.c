#include "shell.h"

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
