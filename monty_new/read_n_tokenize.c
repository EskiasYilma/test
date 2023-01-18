#include "monty.h"

/**
 * read_n_tokenize - reads file line by line and tokenizes line
 * @input: file to read
 * Return: Nothing
 */

void read_n_tokenize(FILE *input)
{
	char *lineptr = NULL, *token = NULL, tokens[1024];
	int i, j = 1;
	stack_t *head = NULL;

	glob_vars.opcode = NULL;
	lineptr = fgets(tokens, 1024, input);
	while (!feof(input))
	{
		token = strtok(lineptr, DELIM);
		i = 0;
		while (token && i < 2)
		{
			if (i == 0)
			{
				if (token[0] == '#')
				{
					glob_vars.opcode = "#";
					j--;
				}
				else
					glob_vars.opcode = token;
				glob_vars.line_number = j;
			}
			if (i == 1)
			{
				glob_vars.argv = token;
			}
			token = strtok(NULL, DELIM);
			i++;
		}
		if (glob_vars.opcode)
		{
			exec_func(glob_vars.opcode)(&head, glob_vars.line_number);
		}
		glob_vars.argv = NULL;
		glob_vars.opcode = NULL, j++;
		lineptr = fgets(tokens, 1024, input);
	}
	free_dlistint(head);
	fclose(input);
}

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
	code_in = glob_vars.opcode, l = glob_vars.line_number;
	dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n", l, code_in);
	exit(EXIT_FAILURE);
}

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
