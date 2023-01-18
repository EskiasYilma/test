#include "monty.h"

/**
 * exec_func - prints errors to stdout
 * @opcode: opcode name
 * Return: Nothing
 */

void (*exec_func(char *opcode))(stack_t **stack, unsigned int line_number)
{
	int i = 0, l = 0;
	char *code_in = NULL;

	instruction_t valid_code[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}
	};
	while (valid_code[i].opcode)
	{
		if (strcmp(opcode, valid_code[i].opcode) == 0)
		{
			return (valid_code[i].f);
		}
		i++;
	}
	code_in = gl_opcode, l = gl_line_number;
	dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n", l, code_in);
	exit(EXIT_FAILURE);
}
