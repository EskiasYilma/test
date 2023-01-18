#include "monty.h"

/**
 * print_error - prints errors to stdout
 * @line_number: line number of the error
 * Return: Nothing
 */

void print_error(char err[10], unsigned int line_number)
{
	dprintf(STDERR_FILENO, "L%d: can't %s, stack empty\n", err, line_number);
}
