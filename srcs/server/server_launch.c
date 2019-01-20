/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** server_launch
*/
#include "./server/Server_init.h"
#include "./server/server.h"
#include "stdio.h"
#include "Handler.h"
#include "gui_commands.h"
#include <signal.h>

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
	if (listen(fd, serv->max_clients) == -1 || serv->max_clients <= 0) {
		my_write(2, "Socket can't be list\n");
		close(fd);
		return (-1);
	}
	serv->fd = fd;
	return (fd);
}

void close_server(t_server *serv)
{
	client_t *cl;
	list_t *client = serv->clients;


	close(serv->fd);
	while (client != 0) {
		cl = (client_t *)client->data;
		close(cl->fd);
		client = client->next;
	}
}

void add_new_client(list_t **clients, t_server *serv)
{
	client_t *client = malloc(sizeof(client_t));
	struct sockaddr_in *addr = malloc(sizeof(struct sockaddr_in));
	socklen_t size = sizeof(struct sockaddr_in);
	int i = 0;

	if (client == 0) {
		my_write(2, "Error on Malloc\n");
		return ;
	}
	if ((client->fd = accept(serv->fd, (struct sockaddr *)addr, &size)) == -1) {
		my_write(2, "Can't accept a new client\n");
		return ;
	}
	if ((i = my_add_data(clients, client)) == -1) {
		my_write(2, "Error on adding client\n");
		close(client->fd);
		return ;
	}
	my_write(client->fd,"WELCOME\n");
    	client_init(&client);
	printf("New Client from IP Adress %s\n", inet_ntoa(addr->sin_addr));
}

void welcome_to(client_t **client, t_server *serv , char *str, list_t **teams) {
	char rpl[80];
	static int user_cnt = 0;

	if (str == NULL)
		return;
	if ((*client)->isGraphical == -1)
		my_write(1, "Le clients n'est rien!\n");
	if ((*client)->isGraphical == -1 && strcmp(str, IDENTIFICATION_GRAPHICAL) == 0) {
		(*client)->isGraphical = 1;
		my_write(1, "Le clients est graphique !\n");
		(*client)->position.x = -1;
		(*client)->position.y = -1;
		msz(*client, serv, NULL);
		mct(*client, serv, NULL);
	} else if ((*client)->isGraphical == -1 && (*client)->team == NULL)
			getTeams(str, teams, client);
	if ((*client)->isGraphical == 0 ) {
		my_write(1,"le client est une ia\n");
        	sprintf(rpl,"%d\n",((*client)->team->max_client - (*client)->team->current_user));
		my_write((*client)->fd, rpl);
		(*client)->id = user_cnt;
		sprintf(rpl,"%ld %ld\n",serv->map->size_x,serv->map->size_y);
		my_write((*client)->fd, rpl);
		new_player(*client, serv, NULL);
		user_cnt++;
	}
}

void getTeams(char *str, list_t **teams, client_t **client)
{
	t_team *team;
	list_t *tmp = *teams;

	while (tmp != 0) {
		team = (t_team *)tmp->data;
		if (str == NULL)
			return;
        	str = strtok(str,"\n\r");
		if (strcmp(str,team->name) == 0 && team->current_user < team->max_client) {
			team->current_user += 1;
			(*client)->isGraphical = 0;
			(*client)->team = team;
			return;
		}
		tmp = tmp->next;
	}
	my_write((*client)->fd,"ko\n");
}

void client_init(client_t **client)
{
	(*client)->position.x = 0;
	(*client)->position.y = 3;
	(*client)->position.dir = TOP;
	memset((*client)->buf.buffer, 0, BUFF_SIZE);
	(*client)->buf.tail = 0;
	(*client)->buf.head = 0;
	(*client)->isGraphical = -1;
    	(*client)->level = 1;
	(*client)->team_name = NULL;
    	(*client)->team = NULL;
}

void set_fds(t_server *serv, int fd_server)
{
	client_t *cl;
	list_t *client = serv->clients;

	FD_ZERO(serv->readfds);
	FD_SET(fd_server, serv->readfds);
	if (!client)
		return;
	while (client != 0) {
		cl = (client_t *)client->data;
		if (cl == 0)
			break;
		FD_SET(cl->fd, serv->readfds);
		client = client->next;
	}
}

int h_select(t_server *serv, int fd_serv, list_t **teams)
{
	client_t *cl;
	list_t **clients = &(serv->clients);
	list_t *tmp = *clients;

	if (select(get_max_fd(*clients, fd_serv), serv->readfds, NULL, NULL, NULL) == -1){
		printf("client deconnecté");
		return (1);
	}
	while (tmp != 0) {
		cl = (client_t *)((tmp)->data);
		if (FD_ISSET(cl->fd, serv->readfds))
            		Handler_choice(&cl,serv,teams);
		tmp = tmp->next;
	}
	if (FD_ISSET(fd_serv, serv->readfds))
		add_new_client(clients, serv);
	return (0);
}

void server_init (t_server *serv, t_option *opt, list_t **teams)
{
	serv->clients = NULL;
	serv->max_clients = 2 * opt->max_clients;
	if (opt == NULL || create_server(serv,opt->port) == -1){
		printf("Impossible de creer le serveur\n");
		close_server(serv);
		exit(0);
	}
	serv->map = create_map(opt->x, opt->y);
	serv->freq = opt->freq;
	serv->max_client_team = opt->max_clients;
	*teams = opt->teams;
	free(opt);
}

void start_server(t_server *serv, list_t **teams)
{
	fd_set readfs;
	serv->readfds = &readfs;
	int run = 0;

	while (run == 0) {
		set_fds(serv, serv->fd);
		run = h_select(serv, serv->fd, teams);
	}
	close_server(serv);
}

int get_max_fd(list_t *client, int fd_server)
{
	int max = fd_server;
	client_t *cl;

	if (!client)
		return (max + 1);
	while (client != 0) {
		cl = (client_t *)client->data;
		if (cl != 0 && (cl->fd) > max)
			max = cl->fd;
		client = client->next;
	}
	return (max + 1);
}
