/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** commands
*/

#include "game.h"
#include "Server_init.h"
#include "string_fct.h"

client_t *get_player(t_server *serv, int id)
{
	list_t *tmp = serv->clients;
	client_t *player = NULL;

	while (tmp != NULL) {
		player = (client_t *)tmp->data;
		if (player && player->id == id)
			return (player);
		tmp = tmp->next;
	}
	return (NULL);
}

void player_position(client_t *client, t_server *serv, char **args)
{
	char msg[128];
	client_t *player;
	int dir;

	if (args != NULL)
		player = get_player(serv, atoi(args[1]));
	else 
		player = client;
	if (!player)
		return;
	switch (client->position.dir) {
		case TOP:
			dir = 1;
			break;
		case RIGHT:
			dir = 2;
			break;
		case DOWN:
			dir = 3;
			break;
		case LEFT:
			dir = 4;
			break;
	};
	sprintf(msg, "ppo %d %d %d %d\n",
		player->id,
		player->position.x,
		player->position.y,
		dir);
	send_to_gui(serv, msg);
}

void player_level(client_t *client, t_server *serv, char **args)
{
	(void) client;
	char msg[128];
	client_t *player = get_player(serv, atoi(args[1]));

	sprintf(msg, "plv %d %d\n",
		player->id,
		player->level);
	send_to_gui(serv, msg);
}

void player_inv(client_t *client, t_server *serv, char **args)
{
	(void)client;
	char *msg = malloc(sizeof(char)* 256);
	char buff[128];
	int size = 0;

	while (size < 2 && args[size] != 0) {
		size++;
	}
	if (size < 2 || !msg)
		return;
	client_t *player = get_player(serv, atoi(args[1]));
	if (!player)
		return;
	sprintf(msg, "pin %d %d %d %d",
		player->id,
		player->position.x,
		player->position.y,
		player->inventory[STONE_TYPES +1]);
	for (int i = 0; i < STONE_TYPES; i++){
		sprintf(buff, " %d", player->inventory[i]);
     		msg = re_concat(msg, buff);
		if (i == (STONE_TYPES - 1))
     			msg = re_concat(msg, "\n");
	}
	send_to_gui(serv, msg);
	free(msg);
}

void new_player(client_t *client, t_server *serv, char **args)
{
	char msg[128];
	(void)serv;
	(void)args;
	int dir;

	switch (client->position.dir) {
		case TOP:
			dir = 1;
			break;
		case RIGHT:
			dir = 2;
			break;
		case DOWN:
			dir = 3;
			break;
		case LEFT:
			dir = 4;
			break;
	};


	sprintf(msg, "pnw %d %d %d %d %d %s\n",
		client->id,
		client->position.x,
		client->position.y,
		dir,
		client->level,
		client->team->name);
	send_to_gui(serv, msg);
}

void pex(client_t *client, t_server *serv, char **args)
{
	char msg[128];
	(void)serv;
	(void)args;

	sprintf(msg, "pex %d\n", client->id);
	send_to_gui(serv, msg);
}
