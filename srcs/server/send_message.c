/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** send_message
*/

#include "Server_init.h"

int send_message(int fd, char *msg)
{
	if (my_write(fd, msg) == 1) {
		return(-1);
	}
	return (0);
}

int send_to_all(t_server *serv, char *msg)
{
	list_t *node = serv->clients;
	client_t *client;

	while(node != NULL) {
		client = (client_t *) node->data;
		if (client->isGraphical == 0 
		&& send_message(client->fd, msg) == -1)
			return (-1);
		node = node->next;
	}
	return (0);
}

int send_to_gui(t_server *serv, char *msg)
{
	list_t *node = serv->clients;
	client_t *client;

	while (node != NULL) {
		client = (client_t *) node->data;
		if (client->isGraphical == 1) {
			if (send_message(client->fd, msg) == -1) {
				return (-1);
			}
		}
		node = node->next;
	}
	return (0);
}

void send_current_level(list_t *clients)
{
	list_t *tmp = clients;
	client_t *cl;
	char rpl[25];

	while (tmp != NULL) {
		cl = (client_t *)tmp->data;
		if (cl != 0) {
			sprintf(rpl,"Current level: %d\n", cl->level);
			my_write(cl->fd,rpl);
		}
		tmp = tmp->next;
	}
}

void send_mgs_to_list(list_t *clients, char *str)
{
	list_t *tmp = clients;
	client_t *cl;

	while (tmp != NULL) {
		cl = (client_t *)tmp->data;
		if (cl != 0) 
			my_write(cl->fd,str);
		tmp = tmp->next;
	}
}

void update_level_list(list_t *clients)
{
	list_t *tmp = clients;
	client_t *cl;

	while (tmp != NULL) {
		cl = (client_t *)tmp->data;
		if (cl != 0)
			cl->level = cl->level + 1;
		tmp = tmp->next;
	}
}