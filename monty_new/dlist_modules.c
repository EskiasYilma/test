#include "monty.h"

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
