/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** commands 2
*/

#include "Server_init.h"
#include "game.h"
#include "gui_commands.h"

void msz(client_t *client, t_server *serv, char **args)
{
  char msg[128];
  (void)args;

  sprintf(msg, "msz %ld %ld\n", serv->map->size_x, serv->map->size_y);
  send_message(client->fd, msg);
}

void bct_aux(client_t *client, t_server *serv, int x, int y)
{
  char msg[128];

  memset(msg, 0, 128);
  sprintf(msg, "bct %d %d %d %d %d %d %d %d %d\n",
  x, y,
  serv->map->tiles[x][y]->stones[STONE_TYPES],
  serv->map->tiles[x][y]->stones[linemate],
  serv->map->tiles[x][y]->stones[deraumere],
  serv->map->tiles[x][y]->stones[sibur],
  serv->map->tiles[x][y]->stones[mendiane],
  serv->map->tiles[x][y]->stones[phiras],
  serv->map->tiles[x][y]->stones[thystame]);
  send_message(client->fd, msg);
}

void bct(client_t *client, t_server *serv, char **args)
{
  int x = atoi(args[1]);
  int y = atoi(args[2]);

  bct_aux(client, serv, x, y);
}

void mct(client_t *client, t_server *serv, char **args)
{
	(void) args;
        for (size_t i = 0; i < serv->map->size_x; i++) {
		for (size_t j = 0; j < serv->map->size_y; j++) {
			bct_aux(client, serv, i, j);
			usleep(50000);
		}
	}
}

void tna(client_t *client, t_server *serv, char **args)
{
  (void) args;
  (void) client;
  list_t *tmp = serv->teams;
  t_team *team;
  char msg[128];

  while (tmp != NULL) {
        team = (t_team *)tmp->data;
        if (team != 0 && team->name != 0) {
            sprintf(msg,"%s\n",team->name);
            send_to_gui(serv,msg);
        }
        tmp = tmp->next;
  }
}
