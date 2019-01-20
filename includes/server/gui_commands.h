/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** commands
*/

#ifndef GUI_COMMANDS_H
#define GUI_COMMANDS_H

#include "game.h"
#include "Server_init.h"

void player_position(client_t *client, t_server *serv, char **args);
void player_level(client_t *client, t_server *serv, char **args);
void player_inv(client_t *client, t_server *serv, char **args);
void new_player(client_t *client, t_server *serv, char **args);
void pex(client_t *client, t_server *serv, char **args);
void msz(client_t *client, t_server *serv, char **args);;
void bct(client_t *client, t_server *serv, char **args/* int x, int y*/);
void mct(client_t *client, t_server *serv, char **args);
void pbc(client_t *client, t_server *serv, char **args /* char *broadcast*/);
void pic(client_t *client, t_server *serv, char **args);
void pie(client_t *client, t_server *serv, char **args /* int result*/);
void seg(client_t *client, t_server *serv, char **args /* char *team */);
void pdi(client_t *client, t_server *serv, char **args);
void pgt(client_t *client, t_server *serv, char **args /* t_stone ressource*/);
void pdr(client_t *client, t_server *serv, char **args /*t_stone ressource */);
void tna(client_t *client, t_server *serv, char **args);
#endif
