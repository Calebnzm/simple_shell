#include "shell.h"

/**
 * custom_strcmp - Compare two strings
 * @s1: The first string to compare
 * @s2: The second string to compare
 *
 * This function compares two strings character by character until a
 * difference is found or until the end of both strings is reached.
 *
 * Return: The difference between the ASCII value of the first differing
 * characters in the strings. It will be 0 if the strings are equal.
 */
int custom_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

