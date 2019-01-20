/*
** EPITECH PROJECT, 2018
** my irc
** File description:
** list management
*/

#include "utils.h"

t_list *create_list(void)
{
	t_list *list = malloc(sizeof(*list));

	if (list == NULL) {
		perror("malloc");
	}
	list->next = NULL;
	list->prev = NULL;
	list->data = NULL;
	return (list);
}

void add_elem(t_list **list, void *data)
{
	t_list *elem;

	if (data == NULL) {
		perror("empty data");
	}
	if ((elem = malloc(sizeof(*elem))) == NULL) {
		perror("malloc");
	}
	elem->data = data;
	elem->next = *list;
	(*list)->prev = elem;
	*list = elem;
}

void remove_elem(t_list *elem)
{
	t_list *next = elem->next;
	t_list *prev = elem->prev;

	prev->next = next;
	next->prev = prev;
	free(elem);
}

int get_list_size(t_list *list)
{
	t_list *tmp = list;
	int cpt = 0;
	
	while (tmp != NULL) {
		cpt++;
		tmp = tmp->next;
	}
	return (cpt);
}

void free_list(t_list *list, void (*free_elem)(void *))
{
	if (list != NULL)
	{
		if (list->next != NULL)
			free_list(list->next, free_elem);
		if (free_elem)
			(*free_elem)(list->data);
		free(list);
	}
}
