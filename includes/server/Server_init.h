/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Serveri_init
*/

#ifndef SERVERI_INIT_H_
	#define SERVERI_INIT_H_
	#define BUFF_SIZE 2048
	#define IDENTIFICATION_GRAPHICAL "PharrelWilliams"
	#define NBR_LEVEL 7
	#include <sys/select.h>
	#include <sys/types.h>          /* See NOTES */
	#include <sys/socket.h>
	#include <netdb.h>
	#include "utils.h"
	#include "game.h"
	#include "list.h"
        #include "server.h"

	typedef struct s_server t_server;
	typedef struct client_s client_t;
	typedef struct circ_buf_s circ_buf_t;
	typedef struct cmd_s cmd_t;

	struct circ_buf_s {
		char buffer[BUFF_SIZE];
		int head;
		int tail;
	};

	struct cmd_s {
		char *name;
		int args;
		int delay;
		void (*fun)(client_t *client, t_server *serv, char **arg);
	};

	struct client_s {
		int fd;
		int id;
		int level;
		char *team_name;
        	t_team *team;
		circ_buf_t buf;
		coord position;
		int inventory[STONE_TYPES +1];
		int isGraphical;
	};

	struct s_server {
		list_t *clients;
		t_map *map;
		list_t *teams;
		int max_clients;
		int max_client_team;
		fd_set *readfds;
		int fd;
		int freq;
	};

	int create_server(t_server *serv , int port);
	void server_init (t_server *serv, t_option *opt, list_t **teams);
	void start_server(t_server *serv, list_t **teams);
	int h_select(t_server *serv, int fd_serv,list_t **teams);
	void set_fds(t_server *serv, int fd_server);
	void add_new_client(list_t **clients, t_server *serv);
	void client_init(client_t **client);
	void welcome_to(client_t **client, t_server *serv, char *str, list_t **teams);
	void close_server(t_server *serv);
	int get_max_fd(list_t *client, int fd_server);
	int send_message(int fd, char *str);
	int send_to_all(t_server *serv, char *msg);
	int send_to_gui(t_server *serv, char *msg);
	void send_mgs_to_list(list_t *clients, char *str);
	void send_current_level(list_t *clients);
	void getTeams(char *str, list_t **teams, client_t **client);
	char *lookrecurse(client_t *client,char **res, t_server *serv, coord *cl_pos);
	void getDirection(coord *c, t_map *map);
	char *get_players_on_tile(char *str, list_t *clients, coord *pos);
	list_t *get_nb_players_on_tile(client_t *client, list_t *clients, coord *pos);
	int get_nb_same_lvl(client_t *client, list_t *clients);
	void update_level_list(list_t *clients);
	void update_map(t_tile *tile, const int formula[NBR_LEVEL][STONE_TYPES + 1], int level);

#endif /* !SERVERI_INIT_H_ */
