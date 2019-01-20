/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** server
*/

#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "utils.h"
#include "game.h"
#include "list.h"

#define MAX_CLIENT_CONNECTED 2048
#define FREE 0
#define CLIENT 1

typedef struct s_option t_option;
typedef struct s_team t_team;
typedef struct coordonnee coord;

typedef enum direction {
	TOP = 90,
	RIGHT = 180,
	DOWN = 270,
	                LEFT = 360
} Direction;

struct coordonnee {
	int x;
	int y;
	Direction dir;
};

struct s_option {
	int port;
	int x;
	int y;
	list_t *teams;
	int max_clients;
	int freq;
};

int my_write(int fd, char *str);

struct s_team {
	char *name;
	int current_user;
	int max_client;
	list_t *client;
        coord new_pos;
};

t_option *parse_command_line( int argc, char **argv);
void free_option(t_option *opt);
void add_team_max_client(int maxclient, list_t **teams_list);
#endif
