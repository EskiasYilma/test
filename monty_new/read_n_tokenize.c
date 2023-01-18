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

	gl_opcode = NULL;
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
					gl_opcode = "#";
					j--;
				}
				else
					gl_opcode = token;
				gl_line_number = j;
			}
			if (i == 1)
			{
				gl_argv = token;
			}
			token = strtok(NULL, DELIM);
			i++;
		}
		if (gl_opcode)
		{
			exec_func(gl_opcode)(&head, gl_line_number);
		}
		gl_argv = NULL;
		gl_opcode = NULL, j++;
		lineptr = fgets(tokens, 1024, input);
	}
	free_dlistint(head);
	fclose(input);
}
