#ifndef _MONTY_H_
#define _MONTY_H_
#define  _POSIX_C_SOURCE 200809L
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

/*extern variable, stack or queue*/

extern char *flag;

#define BUF_LENGTH 1024

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcoode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void push(stack_t **s, unsigned int line_number, char *num);

void pall(stack_t **s, unsigned int line_number);

void execute(stack_t **h, char *line, unsigned int line_number);
void free_stack(stack_t *h);
void flush_buffer(char *buffer, size_t size);
void fill_buffer(char **buf, size_t *size, char c, size_t index);

#endif
