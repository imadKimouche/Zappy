/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** annexe
*/
#include "list.h"
#include <stdio.h>

list_t *my_find_node(list_t *list, void *data)
{
	if (list == 0 || data == 0)
		return (NULL);
	while (list != 0 && list->data != data)
		list = list->next;
	return (list);
}

void my_delete_node(list_t **list, list_t *node)
{
	list_t *tmp = *list;

	if (list == 0 || *list == 0 || node == 0 ) {
		return ;
	}
	if (*list == node) {
		*list = (*list)->next;
		node->next = 0;
		return ;
	}
	while (tmp->next != 0) {
		if (tmp->next == node) {
			tmp->next = node->next;
			node->next = 0;
			return ;
		}
		tmp = tmp->next;
	}
}

void my_delete_data(list_t **list, void *data)
{
	list_t *tmp = *list;

	if (list == 0 || *list == 0 || data == 0 )
		return ;
	while ((*list)->data == data)
		*list = (*list)->next;
	while (tmp->next != 0) {
		if (tmp->next->data == data)
			tmp->next = tmp->next->next;
		tmp = tmp->next;
	}
}

void my_delete_all_list(list_t *list)
{
	list_t *tmp;

	while (list != 0) {
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

list_t *my_create_node(void *data)
{
	list_t *node = malloc(sizeof(list_t));

	if (node == NULL)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}

int my_add_node(list_t **list, list_t *node)
{
	list_t *tmp = *list;
	int i = 0;

	if (node == NULL)
		return (-1);
	if (*list == NULL) {
		*list = node;
		return (i);
	}
	while (tmp->next != 0) {
		tmp = tmp->next;
		i++;
	}
	tmp->next = node;
	return (i);
}

int my_add_data(list_t **list, void *data)
{
	list_t *tmp = *list;
	int i = 0;

	if (data == NULL)
		return (-1);
	if (*list == NULL && (*list = my_create_node(data)))
		return (i);
	else if (*list == NULL)
		return (-1);
	while (tmp->next != 0) {
		tmp = tmp->next;
		i++;
	}
	if ((tmp->next = my_create_node(data)) == NULL)
		return (-1);
	return (i + 1);
}

int my_list_size(list_t *list)
{
	list_t *tmp = list;
	int cpt = 0;

	while (tmp != NULL) {
		cpt++;
	        tmp = tmp->next;
	}
	return (cpt);
}
