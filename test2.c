#include "monty.h"

/**
 * *****READ ME FIRST ******
 * The process goes from top to bottom.
 * global variables are declared because the functions and instruction struct wont take more than 2 varaiables
 * global variables should be substituted by a global struct inorder to split this file into a number of functions and since you cant call global variables more than once (include monty.h will be called on all files and it will raise an error that the variables were declared multiple times)
 * so we should use a struct that looks sth like this
 * typedef struct global_s
    {
        FILE *file_i;
        char *opcode;
        char *argv;
        unsigned int line_number;
    } global_t;


    extern global_t glob_vars;
    global_t glob_vars;
 * So now when you refer to global variables it will be "glob_vars.argv, glob_vars.opcode .. " instead of gl_argv, gl_opcodes ...
 *
 * main - check no of args, check file validity and go to read file and tokenize
 * read_n_tokenize - instead of getline (was giving me errors) i used fgets to read the file - > tokenize - > set global variables and pass to exec_funct
 * exec_func - compares global_vars with instruction_t opcodes and pass them to their respective functions or error
 * after this its just dlist operations - i imported those fucntions from 0X17 tasks
 */


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

    gl_opcode = NULL;

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
                /* dont mind this part -- */
                if (token[0] == '#')
                {
                    gl_opcode = "#";
                    j--;
                }

                else
                    gl_opcode = token;
                /* till this part for now */
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
        gl_opcode = NULL;
        j++;
        lineptr = fgets(tokens, 1024, input);
    }
    free_dlistint(head);
    fclose(input);
}

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

void push(stack_t **stack, unsigned int line_number)
{
    (void) line_number;
    if (gl_argv != NULL && _isdigit() != 0)
    {
        add_dnodeint(stack, atoi(gl_argv));
        return;
    }
    dprintf(STDERR_FILENO, "L%d: can't pint, stack empty\n", gl_line_number);
    exit(EXIT_FAILURE);
}

/**
 * pall - function to print elements of linked list
 * @stack: pointer to head of stack
 * @line_number: number of the line in the bytecode file
 * Return: Nothing
 */

void pall(stack_t **stack, unsigned int line_number)
{
    (void) line_number;
    print_dlistint(*stack);
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

/**
 * add_dnodeint - adds a new node at the beginning of 'dlistint_t' list
 * @head: position of dlistint_t
 * @n: int to add
 * Return: The address of the new element or NULL if it failed
 */

stack_t *add_dnodeint(stack_t **head, const int n)
{
    stack_t *new_head;

    if (head == NULL)
        return (NULL);
    new_head = malloc(sizeof(stack_t));
    if (new_head == NULL)
    {
        free(new_head);
        return (NULL);
    }
    new_head->n = n;
    new_head->prev = NULL;
    new_head->next = (*head);
    if ((*head) != NULL)
        (*head)->prev = new_head;
    (*head) = new_head;
    return (new_head);
}

/**
 * print_dlistint - prints all the elements of a dlistint_t list.
 * @h: pointer to a doubly linked list
 * Return: number of nodes
 */

size_t print_dlistint(const stack_t *h)
{
    size_t count = 0;

    if (h == NULL)
        return (0);
    while (h != NULL)
    {
        count++;
        printf("%d\n", h->n);
        h = h->next;
    }
    return (count);
}



int _isdigit(void)
{
    int i;

    i = 0;
    if (gl_argv[0] == '-')
        i++;
    while (gl_argv[i])
    {
        if (!isdigit(gl_argv[i]))
            return (0);
        i++;
    }
    return (1);
}
