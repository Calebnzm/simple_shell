#include <stddef.h>
#include "shell.h"
/**
 * custom_strncmp - Compare two strings up to n characters
 * @s1: The first string
 * @s2: The second string
 * @n: The maximum number of characters to compare
 *
 * Return: 0 if strings are equal up to n characters,
 * negative value if s1 < s2,
 *         positive value if s1 > s2
 */
int custom_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
	/* Check for the end of the strings or if characters don't match */
		if (s1[i] == '\0' || s1[i] != s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0); /* Both strings are equal up to n characters */
}
