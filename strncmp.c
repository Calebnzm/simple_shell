#include "shell.h"

/**
* my_strncmp - compare the first n characters of two strings.
* @s1: pointer to first string
* @s2: pointer to second string
* @n: number of caharacyers
*
* Return: zero
*/
int my_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		if (s1[i] == '\0')
		{
			break;
		}
	}
	return (0);
}
