/*
** EPITECH PROJECT, 2018
** my irc
** File description:
** utils header
*/

#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

/* Gestion de liste */

typedef struct s_list {
	void *data;
	struct s_list *next;
	struct s_list *prev;
} t_list;

t_list *create_list(void);
void add_elem(t_list **list, void *data);
void remove_elem(t_list *elem);
int get_list_size(t_list *list);
void free_list(t_list *list, void (*free_elem)(void *));

/* Buffer circulaire */

typedef struct s_cbuff {
	size_t head;
        size_t tail;
	size_t size;
	int empty;
	char *buff;
} t_cbuff;

t_cbuff *create_buff(size_t size);
void reset_buff(t_cbuff *buff);
char *read_buff(t_cbuff *buff);
void write_buff(t_cbuff *buff, char *str);

#endif
