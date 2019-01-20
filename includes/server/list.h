/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list
*/

#ifndef LIST_H_
	#define LIST_H_
	#include <stdlib.h>

	//		LINKED LIST	//
	typedef struct list_s list_t;
	struct list_s {
		void *data;
		list_t *next;
	};
	list_t *my_create_node(void *data);
	list_t *my_find_node(list_t *list, void *data);
	int my_add_node(list_t **list, list_t *node);
	int my_add_data(list_t **list, void *data);
	void my_delete_node(list_t **list, list_t *node);
	void my_delete_data(list_t **list, void *data);
	void my_delete_all_list(list_t *list);
	void my_print_list(list_t *list, void (*my_print)(void *data));
	int my_list_size(list_t *list);
#endif /* !LIST_H_ */
