#include "monty.h"

/**
 * _isdigit - checks if passed arguement is an integer string
 * Return: 0 if isdigit else 1
 */

int _isdigit(void)
{
	int i;

	i = 0;
	if (gl_argv[0] == '-')
		i++;
	while (gl_argv[i])
	{
		if (!isdigit(gl_argv[i]))
			return (0);
		i++;
	}
	return (1);
}
