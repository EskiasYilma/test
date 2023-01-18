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
