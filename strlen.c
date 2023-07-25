#include "shell.h"

/**
 * custom_strlen - Calculates the length of a string
 * @str: The input string
 *
 * This function calculates the length of the given string by iterating
 * through each character until it encounters the null terminator.
 *
 * Return: The length of the string (success).
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

