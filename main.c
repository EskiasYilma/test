#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 *flush_buffer - cleanup
 *@buffer: a buffer
 *@size: size of buffer
 */
void flush_buffer(char *buffer, size_t size)
{
    size_t i;

    for (i = 0; i < size; ++i)
        buffer[i] = '\0';
}

/**
 * fill_buffer - fill buffer with '\0' char
 * @buf: pointer to buffer
 * @size: pointer to size of buffer
 * @c: char to insert at index
 * @index: index at which to enter char
 * since we need to insert '\0' at end of buffer, check we have room
 * or realloc
 */
void fill_buffer(char **buf, size_t *size, char c, size_t index)
{
    char *p;

    if (!buf || !size)
        return; /*should exit really*/
    if (index >= *size - 1) /*I need 2 free spots at this point*/
    {
        *buf = realloc(*buf, *size * 2);
        if (*buf == NULL)
            return;
        *size = *size * 2;
    }
    p = *buf;
    *(p + index) = c;
}

void push(stack_t **s, unsigned int line_number) {
    stack_t *new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->n = line_number;
    new_node->prev = NULL;
    new_node->next = *s;
    if (*s != NULL)
        (*s)->prev = new_node;
    *s = new_node;
}

void pall(stack_t **s, unsigned int line_number) {
    stack_t *temp = *s;
    if (line_number)
    {
        ;
    }
    while (temp != NULL) {
        printf("%d\n", temp->n);
        temp = temp->next;
    }
}

/**
ssize_t _getline(char **buf, size_t *size, FILE *stream)
{
    size_t index = 0;
    char *line = NULL;
    size_t len = 0;

    if (!buf || !size || !stream)
        return -1;

    if (getline(&line, &len, stream) == -1)
        return -1;
    index = len;
    if (*buf)
        free(*buf);
    *buf = line;
    *size = len;
    return index;
}
*/


/**
 * free_stack - free a stack_t list
 * @h: pointer to the top of the stack
 */
void free_stack(stack_t *h) {
    stack_t *current, *next;

    current = h;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}



/**
 * execute - execute the opcode passed in the line
 * @h: pointer to the top of the stack
 * @line: line to parse and execute
 * @line_number: current line number
 */
void execute(stack_t **h, char *line, unsigned int line_number) {
    int i;
    char *opcode;
    char *token;
    instruction_t ops[] = {
        {"push", push},
        {"pall", pall},
        {NULL, NULL}
    };

    token = strtok(line, " \n\t");
    if (token == NULL || strcmp(token, "") == 0) {
        return;
    }
    opcode = token;

    for (i = 0; ops[i].opcode; i++) {
        if (strcmp(ops[i].opcode, opcode) == 0) {
            ops[i].f(h, line_number);
            return;
        }
    }

    fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
    exit(EXIT_FAILURE);
}





int main(int ac, char **av)
{
    stack_t *h;
    unsigned int line_number;
    ssize_t status;
    char *line;
    size_t length;
    FILE *fp;

    if (ac != 2)
    {
        printf("USAGE: %s file\n", av[0]);
        exit(EXIT_FAILURE);
    }
    h = NULL;
    fp = fopen(av[1], "r");
    if (fp == NULL)
    {
        printf("Error: Can't open file %s\n", av[1]);
        exit(EXIT_FAILURE);
    }
    line_number = 0;
    do {
        ++line_number;
        line = NULL;
        length = 0;
        status = getline(&line, &length, fp);
        if (status > 0)
            execute(&h, line, line_number);
        else
            free(line);
    } while (status >= 0);

    fclose(fp);
    free_stack(h);

    return (0);
}

