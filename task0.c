#include "shell.h"

/**
 * add - Calculate sum.
 * Return: Sum (success), -1 (fail).
 */
int add(void)
{
	int a, b, sum;
	char buffer[100];
	int n;

	srand(time(0));
	a = rand() % 100 + 1;
	b = rand() % 200 + 101;

	/* Use the write function to print the values of a and b */
	n = sprintf(buffer, "a = %d\nb = %d\n", a, b);
	write(STDOUT_FILENO, buffer, n);

	sum = a + b;

	/* Use the write function to print the sum */
	n = sprintf(buffer, "%d\n", sum);
	write(STDOUT_FILENO, buffer, n);

	return (sum);
}

/**
 * main - Add random numbers.
 * Return: Always 0.
 */
int main(void)
{
	add();

	return (0);
}
