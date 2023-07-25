#include "shell.h"

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
