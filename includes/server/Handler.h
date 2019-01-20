/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Handler
*/

#ifndef HANDLER_H_
	#define HANDLER_H_
	#include "Server_init.h"
	#include "string_fct.h"
	void Handler_choice(client_t **client, t_server *serv, list_t **teams);
	void handling_ia(client_t **client, t_server *serv,char *str);
	void handling_Graphical(client_t **client, t_server *serv, char *str);
	void MoveTo(coord *old_po, coord newpos, t_map *map);
	void look(client_t **client,  t_server *serv, char *str);
	void connected_usr(client_t **client,  t_server *serv, char *str);
	void forward(client_t **client, t_server *serv, char *str);
	void right(client_t **client, t_server *serv, char *str);
	void left(client_t **client, t_server *serv, char *str);
	void fork_usr(client_t **client, t_server *serv, char *str);
	void inventory(client_t **client, t_server *serv, char *str);
	void incantation(client_t **client, t_server *serv, char *str);
	void set_object(client_t **client, t_server *serv, char *str);
	void take_object(client_t **client, t_server *serv, char *str);
	void setBuffer(client_t **clt);
	char *read_buffer(client_t **clt);
	void get_next_command(circ_buf_t *circ, char buf[BUFF_SIZE + 1]);
	int increment(int i);
#endif /* !HANDLER_H_ */