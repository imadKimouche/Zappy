/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** server
*/

#include "Network.h"
#include "game.h"
#include "server.h"


int create_server(t_server *serv , int port)
{
	int fd;
	struct sockaddr_in sck_in;
	struct protoent *proto = getprotobyname("TCP");

        sck_in.sin_family = AF_INET;
	sck_in.sin_port = htons(port);
	sck_in.sin_addr.s_addr = INADDR_ANY;
	if ((fd = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1) {
		my_write(2, "Error in intialising socket\n");
		return (-1);
	}
	if (bind(fd, (const struct sockaddr *)&sck_in, sizeof(sck_in)) == -1) {
		my_write(2, "Socket can't be bind\n");
		close(fd);
		return (-1);
	}
	if (listen(fd, serv->max_clients) == -1 || e->max_clients <= 0) {
		my_write(2, "Socket can't be list\n");
		close(fd);
		return (-1);
	}
	serv->fd = fd;
	return (fd);
}

void init_server(t_server *serv, t_option *opt)
{
	printf("heello \n");
	serv->max_clients = get_list_size(opt->teams) * opt->max_clients;
	if (!create_server(serv,opt->port))
		exit(0);
	serv->map = create_map(opt->x, opt->y);
	serv->max_client_team = opt->max_clients;
	//serv->teams = opt->teams;
	free(opt);
}


void set_fds(t_server *serv)
{
	client_sc *cl;
	list_n *tmp = serv->clients;

	FD_ZERO(&(serv->readfds));
	FD_SET(serv->fd, &(serv->readfds));
	while (tmp != 0) {
		cl = (client_sc *)tmp->data;
		FD_SET(cl->fd, &(serv->readfds));
		tmp = tmp->next;
	}
}

int my_add_data(list_n **clients, void *data)
{
	list_n *tmp = *clients;
	list_n *node;

	if (tmp == 0)
		return (-1);

	while (tmp->next != 0) {
		tmp = tmp->next;
	}
	node = malloc(sizeof(list_n *));
	if (node == NULL)
		return (-1);
	node->data = data;
	node->next = 0;
	tmp->next = node;
}

void add_new_client(list_n **clients, int fd)
{
	client_sc *client = malloc(sizeof(client_sc));
	struct sockaddr_in *addr = malloc(sizeof(struct sockaddr_in));
	socklen_t size = sizeof(struct sockaddr_in);
	int i = 0;

	if (client == 0) {
		my_write(2, "Error on Malloc\n");
		return ;
	}
	if ((client->fd = accept(fd, (struct sockaddr *)addr, &size)) == -1) {
		my_write(2, "Can't accept a new client\n");
		return ;
	}
	if ((i = my_add_data(clients, client)) == -1) {
		my_write(2, "Error on adding client\n");
		close(client->fd);
		return ;
	}
	//iniclient_t(client);
	printf("New Client from IP Adress %s\n", inet_ntoa(addr->sin_addr));
}

int get_max_fd(list_n *client, int fd_server)
{
	int max = fd_server;
	client_sc *cl;

	while (client != 0) {
		cl = (client_sc *)client->data;
		if ((cl->fd) > max)
			max = cl->fd;
		client = client->next;
	}
	return (max + 1);
}

void h_select(t_server *serv)
{
	client_sc *cl;
	list_n *tmp = serv->clients;
	int error = 0;

	error = select(get_max_fd(serv->clients, serv->fd), &(serv->readfds), NULL, NULL, NULL);

	while (tmp != 0) {
		cl = (client_sc *)((tmp)->data);
		if (FD_ISSET(cl->fd, &(serv->readfds)))
			//handle_client(cl, clients, chanels);
		tmp = tmp->next;
	}
	if (FD_ISSET(serv->fd, &(serv->readfds)))
		add_new_client(&(serv->clients), fd_serv);
}





void start_server(t_option *opt)
{
	t_server serv;

	init_server(&serv,opt);
	while (42) {
		set_fds(&serv);
		h_select(&serv);
	}
}
