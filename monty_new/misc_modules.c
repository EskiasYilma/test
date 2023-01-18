#include "monty.h"

/**
 * _isdigit - checks if passed arguement is an integer string
 * Return: 0 if isdigit else 1
 */

int _isdigit(void)
{
	int i;

	i = 0;
	if (glob_vars.argv[0] == '-')
		i++;
	while (glob_vars.argv[i])
	{
		if (!isdigit(glob_vars.argv[i]))
			return (0);
		i++;
	}
	return (1);
}
