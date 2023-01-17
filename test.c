/**
int main(int argc, char *argv[])
{
    char *buf = NULL;
    size_t size = 0;
    FILE *file;
    stack_t *stack = NULL;
    unsigned int line_number = 0;
    char *token;
    char *num;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (_getline(&buf, &size, file) != -1)
    {
        line_number++;
        token = strtok(buf, " \n\t");
        if (token == NULL || strcmp(token, "") == 0)
        {
            continue;
        }
        if (strcmp(token, "push") == 0)
        {
            num = strtok(NULL, " \n\t");
            if (num == NULL)
            {
                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                exit(EXIT_FAILURE);
            }
            push(&stack, line_number, num);
        }
        else if (strcmp(token, "pall") == 0)
        {
            pall(&stack, line_number);
        }
        else
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, token);
            exit
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include "monty.h"

#define BUF_LENGTH 1024

int push(stack_t **h, char *line, unsigned int l)
{
    char *start_n;
    stack_t *node;

    start_n = reach_number(line);
    if (start_n == NULL)
    {
        printf("L%d: usage: push integer\n", l);
        free(line);
        return (-1);
    };

    if (_strcmp(flag, "stack") == 0)
        node = add_node(h, atoi(start_n));
    else
        node = add_node_end(h, atoi(start_n));

    free(line);
    if (node == NULL)
    {
        puts("Error: malloc failed");
        return (-1);
    }
    return (0);
}



void pall(stack_t **head, unsigned int l)
{
    stack_t *h;
    (void) l;

    if (!head)
        return;
    h = *head;
    while (h != NULL)
    {
        printf("%d\n", h->n);
        h = h->next;
    }
}
ssize_t _getline(char **buf, size_t *size, FILE *stream)
{
    size_t index = 0;
    char *p;

    if (!buf || !size || !stream)
        return -1;

    if (!*buf) {
        *size = BUF_LENGTH;
        *buf = malloc(*size * sizeof(char));
        if (*buf == NULL)
            return -1;
    }

    if (fgets(*buf, *size, stream) == NULL) {
        if (feof(stream))
            return -1;
    }

    p = strchr(*buf, '\n');
    if (p != NULL) {
        *p = '\0';
        index = p - *buf;
    } else {
        index = strlen(*buf);
    }
    return index;
}
int execute(stack_t **h, char *line, unsigned int line_number)
{
    instruction_t instr[] = {
        {"pall", pall},
        {NULL, NULL}
    };
    int i, push_return;
    char *start_c;

    start_c = skip_spaces(line);
    if (start_c == NULL)
    {
        free(line);
        return (1);
    }
    if (_strncmp(start_c, "push", _strlen("push")) == 0)
    {
        push_return = push(h, line, line_number);
        return ((push_return == 0) ? 0 : -1);
    }
    for (i = 0; instr[i].opcode; ++i)
    {
        if (_strncmp(start_c, instr[i].opcode, _strlen(instr[i].opcode)) == 0)
        {
            free(line), (instr[i].f)(h, line_number);
            return (0);
        }
    }
    printf("L%d: unknown instruction ", line_number);
    while (*start_c && (*start_c != ' ' && *start_c != '\t'))
        putchar(*start_c++);
    putchar('\n');
    free(line);
    return (-1);
}

int main(int ac, char **av)
{
    stack_t *h;
    int exec_err, fp;
    unsigned int line_number;
    ssize_t status;
    char *line;
    size_t length;

    if (ac != 2)
    {
        printf("USAGE: monty file\n"), exit(EXIT_FAILURE);
    }
    h = NULL;
    fp = open(av[1], O_RDONLY);
    if (fp == -1)
    {
        printf("Error: Can't open file %s\n", av[1]);
        exit(EXIT_FAILURE);
    }
    line_number = 0;
    do {
        ++line_number;
        line = NULL;
        length = 0;
        status = _getline(&line, &length, fp);
        if (status > 2)
        {
            exec_err = execute(&h, line, line_number);
            if (exec_err == -1)
                status = -2;
        }
        else
            free(line);
    } while (status >= 0);

    close(fp);
    free_stack(h), h = NULL;
    if (status == -1)
        return (0);
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])
{
    stack_t *stack = NULL;
    char *buf = NULL;
    size_t size = 0;
    char *token;
    char *num;
    unsigned int line_number = 0;
    instruction_t ops[] = {
        {"push", push},
        {"pall", pall},
        {NULL, NULL}
    };
    FILE *file;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }
    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (_getline(&buf, &size, file) != -1)
    {
        line_number++;
        token = strtok(buf, " \n\t");
        if (token == NULL || strcmp(token, "") == 0)
            continue;
        num = strtok(NULL, " \n\t");
        for (int i = 0; ops[i].opcode; i++)
        {
            if (strcmp(ops[i].opcode, token) == 0)
            {
                ops[i].f(&stack, line_number, num);
                break;
            }
        }
    }

    free_stack(stack);
    free(buf);
    fclose(file);
    return (EXIT_SUCCESS);
}
*/
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include "monty.h"

#define BUF_LENGTH 1024

ssize_t _getline(char **buf, size_t *size, FILE *stream)
{
    size_t index = 0;
    char *p;

    if (!buf || !size || !stream)
        return -1;

    if (!*buf) {
        *size = BUF_LENGTH;
        *buf = malloc(*size * sizeof(char));
        if (*buf == NULL)
            return -1;
    }

    if (fgets(*buf, *size, stream) == NULL) {
        if (feof(stream))
            return -1;
    }

    p = strchr(*buf, '\n');
    if (p != NULL) {
        *p = '\0';
        index = p - *buf;
    } else {
        index = strlen(*buf);
    }
    return index;
}

void push(stack_t **s, unsigned int line_number, char *num) {
    stack_t *new_node = malloc(sizeof(stack_t));
    if (line_number)
    {
        ;
    }
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->n = atoi(num);
    new_node->prev = NULL;
    new_node->next = *s;
    if (*s != NULL)
        (*s)->prev = new_node;
    *s = new_node;
}

void pall(stack_t **head, unsigned int l)
{
    stack_t *h;
    (void) l;

    if (!head)
        return;
    h = *head;
    while (h != NULL)
    {
        printf("%d\n", h->n);
        h = h->next;
    }
}

void free_stack(stack_t *h) {
    stack_t *current, *next;

    current = h;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(int argc, char *argv[]) {
    stack_t *stack = NULL;
    int line_number = 1;
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t linelen;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while ((linelen = _getline(&line, &bufsize, fp)) != -1) {
        char *token = strtok(line, " \n\t");
        if (strcmp(token, "push") == 0) {
            token = strtok(NULL, " \n\t");
            push(&stack, line_number, token);
        } else if (strcmp(token, "pall") == 0) {
            pall(&stack, line_number);
        } else {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, token);
            exit(EXIT_FAILURE);
        }
        line_number++;
    }

    free(line);
    fclose(fp);
    free_stack(stack);
    return 0;
}

