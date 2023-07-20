#include "shell.h"

/**
 * add - Calculate sum
 * Return: sum(success), -1(fail)
 */

int add(void)
{
	int a, b, sum;

	srand(time(0));
	a = rand() % 100 + 1;
	b = rand() % 200 + 101;

	printf("a = %d \nb = %d\n", a, b);
	sum = a + b;
	printf("%d\n", sum);
	return (sum);
}

/**
 * main - add random numbers
 * Return: 0(always)
 */

int main(void)
{
	add();

	return (0);
}
