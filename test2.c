#include "monty.h"
/**
 * main - entre point
 * @argc: Amount of input arguments
 * @argv: Array of arguments
 *
 * Return: (0) exit succesfull
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

void read_n_tokenize(FILE *input)
{
    char *lineptr = NULL, *token = NULL, tokens[1024];
    size_t len = 0;
    int bytes_read = 0, i, j=1;
    stack_t *head = NULL;

    opcode = NULL;

    (void) len;
    (void) bytes_read;
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
                    opcode = "#";
                    j--;
                }
                else
                    opcode = token;
                line_number = j;
            }
            if (i == 1)
            {
                argv = token;
            }
            token = strtok(NULL, DELIM);
            i++;
        }
        if (opcode)
        {
            exec_func(opcode)(&head, line_number);
        }
        argv = NULL;
        opcode = NULL;
        j++;
        lineptr = fgets(tokens, 1024, input);
    }
    free_dlistint(head);
    fclose(input);
}

void (*exec_func(char *opcode))(stack_t **stack, unsigned int line_number)
{
    int i = 0;
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
    exit(EXIT_FAILURE);
}

void push(stack_t **stack, unsigned int line_number)
{
    (void) line_number;
    (void) stack;
    printf("args (%s) - opcode (%s) - line_no (%d) - Push success!\n", argv, opcode, line_number);
}

void pall(stack_t **stack, unsigned int line_number)
{
    (void) line_number;
    (void) stack;
    printf("args (%s) - opcode (%s) - line_no (%d) - Pall success!\n", argv, opcode, line_number);
}

/**
 * free_dlistint - adds a new node at the end of 'dlistint_t' list
 * @head: position of dlistint_t
 */

void free_dlistint(stack_t *head)
{
    stack_t *temp;

    if (head == NULL)
        return;
    while (head)
    {
        temp = head;
        head = head->next;
        temp->prev = NULL;
        temp->next = NULL;
        free(temp);
    }

}
