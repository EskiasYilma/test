#ifndef _MONTY_H_
#define _MONTY_H_

#define _POSIX_C_SOURCE  200809L
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_LENGTH 1024
#define DELIM " \t\n"

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


char *gl_argv;
unsigned int gl_line_number;
char *gl_opcode;
FILE *byte_file;

/* Read file and tokenize Module */
void read_n_tokenize(FILE *input);
void (*exec_func(char *opcode))(stack_t **stack, unsigned int line_number);

/* op Modules */
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);

/* Doubly linked lists operations */
stack_t *add_dnodeint(stack_t **head, const int n);
size_t print_dlistint(const stack_t *h);
void free_dlistint(stack_t *head);

/* Error Modules */
void print_error(char err[10], unsigned int line_number);

/* Misc Modules */
int _isdigit(void);
#endif
