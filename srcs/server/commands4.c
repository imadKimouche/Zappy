/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** commands 2
*/

#include "Server_init.h"
#include "game.h"
#include "string_fct.h"
#include "gui_commands.h"
#include <string.h>

int str_to_stone(char *str)
{
  if (strcmp(str, "linemate") == 0)
    return linemate;
  if (strcmp(str, "deraumere") == 0)
    return deraumere;
  if (strcmp(str, "sibur") == 0)
    return sibur;
  if (strcmp(str, "mendiane") == 0)
    return mendiane;
  if (strcmp(str, "phiras") == 0)
    return phiras;
  if (strcmp(str, "thystame") == 0)
    return thystame;
  return (STONE_TYPES + 2);
}

void pdr(client_t *client, t_server *serv, char **args)
{
    (void)serv;
    const char *graph_res[STONE_TYPES + 1] = { "food", "linemate", "deraumere" ,"sibur" ,"mendiane" ,"phiras" ,"thystame" };
    char buff[128];
    
    if (!args)
      return;
    for (int i = 0; i < (STONE_TYPES + 1); i++) {
        if (strcmp(args[0], graph_res[i]) == 0){
          sprintf(buff, "pdr %d %d\n", client->id, i);
	        send_to_gui(serv, buff);
          break;
        }
    }  
}

void pgt(client_t *client, t_server *serv, char **args)
{
    (void)serv;
    (void)client;
    const char *graph_res[STONE_TYPES + 1] = { "food", "linemate", "deraumere" ,"sibur" ,"mendiane" ,"phiras" ,"thystame" };
    char buff[128];

    if (!args)
      return;
    for (int i = 0; i < (STONE_TYPES + 1); i++) {
        if (strcmp(args[0], graph_res[i]) == 0){
          sprintf(buff, "pgt %d %d\n", client->id, i);
          send_to_gui(serv, buff);
          break;
        }
    }  
}

void pdi(client_t *client, t_server *serv, char **args)
{
    char msg[128];
    (void)serv;
    (void)args;

    sprintf(msg, "pdi %d\n", client->id);
    send_to_gui(serv,msg);
}

void seg(client_t *client, t_server *serv, char **args)
{
  char msg[128];
  char *team = args[1];
  (void)serv;

  sprintf(msg, "seg %s\n", team);
  send_message(client->fd, msg);
}
