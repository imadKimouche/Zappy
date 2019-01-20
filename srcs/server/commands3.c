/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** commands 2
*/

#include "Server_init.h"
#include "game.h"
#include "string_fct.h"
#include "string.h"
#include "gui_commands.h"
#include "tiles.h"

void pbc(client_t *client, t_server *serv, char **args)
{
  char *broadcast = args[1];
  char *msg = malloc(sizeof(char) * (24 + strlen(broadcast)));
  (void)serv;

  sprintf(msg, "pbc %d %s\n", client->id, broadcast);
  send_message(client->fd, msg);
  free(msg);
}

void pic(client_t *client, t_server *serv, char **args)
{
    (void)args;
    char buff[25];
    char *msg;
    list_t *node = get_nb_players_on_tile(client,serv->clients,&(client->position));
    client_t *tmp;

    if ((msg = malloc(sizeof(char) * 50)) == 0)
        return;
    sprintf(msg, "pic %d %d %d %d",
    client->position.x, client->position.y,
    client->level, client->id);

    while (node != NULL) {
        tmp = (client_t *)node->data;
        if (tmp != 0) {
            sprintf(buff, " %d", tmp->id);
            msg = re_concat(msg, buff);
        }
        node = node->next;
    }
    msg = re_concat(msg, "\n");
    send_to_gui(serv, msg);
    free(msg);
}

void pie(client_t *client, t_server *serv, char **args)
{
  (void)serv;
  char msg[128];
  char *result = args[0];

  sprintf(msg, "pie %d %d %s\n",
  client->position.x,
  client->position.y,
  result);
  send_to_gui(serv, msg);
}
