#include "monty.h"

/**
 * push - adds node at the beginning of the stack
 * @stack: head pointer to stack
 * @line_number: line number of the file
 * Return: Nothing
 */

void push(stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	if (glob_vars.argv != NULL && _isdigit() != 0)
	{
		add_dnodeint(stack, atoi(glob_vars.argv));
		return;
	}
	dprintf(STDERR_FILENO, "L%d: usage: push integer\n", glob_vars.line_number);
	exit(EXIT_FAILURE);
}

/**
 * pall - print elements of a doubly linked list
 * @stack: head pointer to stack
 * @line_number: line number of the file
 * Return: Nothing
 */

void pall(stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	print_dlistint(*stack);
}
