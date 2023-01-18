#include "monty.h"
/**
 * main - entry point
 * @argc: arguement count
 * @argv: arguement vector
 *
 * Return: 0 (SUCCESS)
 */

int main(int argc, char *argv[])
{
	char *filename = argv[1];
	FILE *fp = NULL;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	read_n_tokenize(fp);
	exit(EXIT_SUCCESS);
}
