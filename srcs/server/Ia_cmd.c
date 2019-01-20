/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Handler
*/
#include "Handler.h"
#include "utils.h"
#include <string.h>
#include "Server_init.h"
#include "gui_commands.h"
#include "tiles.h"

void forward(client_t **client, t_server *serv, char *str)
{
	(void)str;
	printf("\nForward action \n (x:%d/y:%d) Dir: %d\n",(*client)->position.x,(*client)->position.y,(*client)->position.dir);
    	getDirection(&((*client)->position),serv->map);
	printf("\nForward apres action \n (x:%d/y:%d) Dir: %d\n",(*client)->position.x,(*client)->position.y,(*client)->position.dir);
	player_position(*client, serv, NULL);
	my_write((*client)->fd,"ok\n");
}

void MoveTo(coord *old_pos, coord newpos, t_map *map)
{
	if (newpos.x >= (int)map->size_x)
		newpos.x = 0;
	else if (newpos.x < 0)
			newpos.x = (map->size_x - 1);
	if (newpos.y >= (int)map->size_y)
		newpos.y = 0;
	else if (newpos.x < 0)
		newpos.x = (map->size_y - 1);
	old_pos->x = newpos.x;
	old_pos->y = newpos.y;
	old_pos->dir = newpos.dir;
}

void right(client_t **client,  t_server *serv, char *str)
{
    (void)serv;
	(void)str;
	int newpos = (*client)->position.dir + 90;

	if (newpos > LEFT)
		(*client)->position.dir = TOP;
	else
		(*client)->position.dir = newpos;
	player_position(*client, serv, NULL);
	my_write((*client)->fd,"ok\n");
}

void left(client_t **client,  t_server *serv, char *str)
{
    	(void)serv;
	(void)str;
	int newpos = (*client)->position.dir - 90;

	if (newpos < TOP)
		(*client)->position.dir = LEFT;
	else
		(*client)->position.dir = newpos;
	player_position(*client, serv, NULL);
	my_write((*client)->fd,"ok\n");
}

void connected_usr(client_t **client,  t_server *serv, char *str)
{
	(void)serv;
	(void)str;
	char rpl[80];

	if ((*client)->team == NULL)
		return;
	sprintf(rpl,"%d\n",((*client)->team->max_client - (*client)->team->current_user));
	my_write((*client)->fd,rpl);
}

void inventory(client_t **client, t_server *serv, char *str)
{
	(void) serv;
	(void)str;
	char msg[128];
	client_t *player = *client;

	if (!player)
		return;
	memset(msg, 0, 128);
	sprintf(msg, "[ food %d, linemate %d, deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d ]\n",
		player->inventory[6],
		player->inventory[0],
		player->inventory[1],
		player->inventory[2],
		player->inventory[3],
		player->inventory[4],
		player->inventory[5]);
	send_message(player->fd, msg);
}

void getDirection(coord *c, t_map *map)
{
	int y = c->y;
	int x = c->x;

	switch (c->dir) {
		case TOP:
			x += 1;
			break;
		case RIGHT:
			y += 1;
			break;
		case DOWN:
			x -= 1;
			break;
		case LEFT:
			y -= 1;
			break;
	};
	if (x >= (int)(map->size_x))
			x = 0;
	else if (x < 0)
			x = (int)(map->size_x - 1);
	if (y >= (int)(map->size_y))
		y = 0;
	else if (y < 0)
		y = (int)(map->size_y - 1);
	c->x = x;
	c->y = y;
}

char *get_players_on_tile(char *str, list_t *clients, coord *pos)
{
	list_t *tmp = clients;
	client_t *cl;

	while (tmp != NULL) {
		cl = (client_t *)tmp->data;
		if (cl != NULL && cl->position.x == pos->x && cl->position.y == pos->y)
			return re_concat(str, " player");
		tmp = tmp->next;
	}
	return str;
}

list_t *get_nb_players_on_tile(client_t *client, list_t *clients, coord *pos)
{
	list_t *tmp = clients;
	list_t *res = NULL;
	client_t *cl;
	char rpl[80];

	while (tmp != NULL) {
		cl = (client_t *)tmp->data;
		if (client != cl &&  cl != NULL && cl->position.x == pos->x && cl->position.y == pos->y)
			my_add_data(&res,cl);
		tmp = tmp->next;
	}
	sprintf(rpl,"nb de players sur la case :%d \n",my_list_size(res));
	my_write(1,rpl);
	return res;
}

char *lookrecurse(client_t *client, char **res, t_server *serv, coord *cl_pos)
{
	char *str = *res;
	coord n_pos;

	for (int i = 0; i <= client->level; i++){
        n_pos.x = cl_pos->x;
        n_pos.y = cl_pos->y;
        printf("Coordonner Milieu(x:%d/y:%d) direction : %d\n",cl_pos->x,cl_pos->y,cl_pos->dir);
		
		for (int cpt = i; cpt > 0; cpt--) {
			str = re_concat(str, ",");
			if (cl_pos->dir == TOP || cl_pos->dir == DOWN)
				n_pos.y = ((cl_pos->y - cpt) < 0) ? ((int)serv->map->size_y - cpt): (cl_pos->y - cpt);
			else 
				n_pos.x = ((cl_pos->x - cpt) < 0) ? ((int)serv->map->size_x - cpt): (cl_pos->x - cpt);
			str = get_players_on_tile(str,serv->clients,&n_pos);
			str = re_concat(str, get_res_tiles(serv->map->tiles[n_pos.x][n_pos.y]));
			printf("Coordonner Gauche(x:%d/y:%d)\n",n_pos.x,n_pos.y);
		}
		if (i > 0)
			str = re_concat(str, ",");
		str = get_players_on_tile(str,serv->clients,cl_pos);
		str = re_concat(str, get_res_tiles(serv->map->tiles[cl_pos->x][cl_pos->y]));
		for (int cpt = 1; cpt <= i; cpt++) {
			str = re_concat(str, ",");
			if (cl_pos->dir == TOP || cl_pos->dir == DOWN)
				n_pos.y = ((cl_pos->y + cpt) >= (int)serv->map->size_y) ? 0 : (cl_pos->y + cpt);
			else 
				n_pos.x = ((cl_pos->x + cpt) >= (int)serv->map->size_x) ? 0 : (cl_pos->x + cpt);
			str = get_players_on_tile(str,serv->clients,&n_pos);
			str = re_concat(str, get_res_tiles(serv->map->tiles[n_pos.x][n_pos.y]));
            		printf("Coordonner Droite(x:%d/y:%d)\n",n_pos.x,n_pos.y);
		}
		getDirection(cl_pos, serv->map);
		printf("La chaine vaut donc : %s\n",str);
	}
	*res = str;
	return str;
}

void look(client_t **client, t_server *serv, char *str)
{
	(void)str;
	coord cl_pos;
	char *res = malloc(sizeof(char) * 2);
	res[0] = '[';
	res[1] = '\0';

	cl_pos.x = (*client)->position.x;
	cl_pos.y = (*client)->position.y;
	cl_pos.dir = (*client)->position.dir;
	res = lookrecurse((*client),&res,serv, &cl_pos);
	res = re_concat(res, "]\n");
	my_write((*client)->fd,res);
    	my_write(1,res);
}

void fork_usr(client_t **client, t_server *serv, char *str)
{
	(void)str;
	(void)serv;

	t_team *team = (*client)->team;

	team->max_client += 1;
	team->new_pos = (*client)->position;
	my_write((*client)->fd,"ok\n");
	printf("Forkkk passdee !!\n");
}

int get_nb_same_lvl(client_t *client, list_t *clients)
{
	list_t *tmp = clients;
	client_t *tmp_cl;
	int players = 0;

	while (tmp != 0) {
			tmp_cl = (client_t *)tmp->data;
			if (tmp_cl != 0 && client->isGraphical == 0 
			&& client->level == tmp_cl->level)
				players++;
			tmp = tmp->next;
	}
	return players;
}

void incantation(client_t **client, t_server *serv, char *str)
{
	(void)str;
	char *rpl[2] = { "ko", "ok" };
	const int formula[NBR_LEVEL][STONE_TYPES + 1] = {
		{1, 1, 0, 0, 0, 0, 0},
		{2, 1, 1, 1, 0, 0, 0},
		{2, 2, 0, 1, 0, 2, 0},
		{4, 1, 1, 2, 0, 1, 0},
		{4, 1, 2, 1, 3, 0, 0},
		{6, 1, 2, 3, 0, 1, 0},
		{6, 2, 2, 2, 2, 2, 1}
	};
	t_tile *tiles;
	client_t *cl = *client;
	int lvlup = 1;
	list_t *pl_tile = get_nb_players_on_tile(cl,serv->clients,&(cl->position));

	if (cl->level > NBR_LEVEL 
	|| get_nb_same_lvl(cl,pl_tile) != formula[cl->level - 1][0]) {
		my_write(cl->fd,"ko\n");
		return;
	}
	my_add_data(&pl_tile,cl);
	send_mgs_to_list(pl_tile,"Elevation underway\n");
	pic(cl,serv,0);
	tiles = serv->map->tiles[cl->position.x][cl->position.y];
	for (int i = 1; i < STONE_TYPES + 1; i++) {
		if (tiles->stones[i - 1] != formula[cl->level - 1][i]) {
			pie(cl,serv,rpl);
			send_mgs_to_list(pl_tile,"ko\n");
			lvlup = 0;
			break;
		}
	}
	if (lvlup == 0) {
		pie(cl,serv,rpl);
		send_mgs_to_list(pl_tile,"ko\n");
		return;
	}
	rpl[0] = "ok";
	update_map (tiles,formula,cl->level);
	update_level_list(pl_tile);
	send_current_level(pl_tile);
	pie(cl,serv,rpl);
}

void update_map(t_tile *tile, const int formula[NBR_LEVEL][STONE_TYPES + 1], int level)
{
	for (int i = 1; i < STONE_TYPES + 1; i++) {
		if (formula[level - 1][i] > 0) {
			tile->stones[i - 1] = tile->stones[i - 1] - 1; 
		}
	}
}

void take_object(client_t **client, t_server *serv, char *str)
{
	char *pch;
	t_tile *tiles;
	int i = 0;
	const char *stones[8] = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame","food", 0};
	char **grph_str = malloc(sizeof(char *) * 1);
	
	pch = strtok(str," \n");
	if (pch == NULL)
		my_write((*client)->fd,"ko\n");
	if (grph_str == NULL)
		return;
	tiles = serv->map->tiles[(*client)->position.x][(*client)->position.y];
	while (i < 7) {
		if (strcmp(pch, stones[i]) == 0 && tiles->stones[i] > 0) {
			tiles->stones[i] = tiles->stones[i] - 1;
			(*client)->inventory[i] = (*client)->inventory[i] + 1;
          		my_write((*client)->fd, "ok\n");
			grph_str[0] = pch;
			pgt((*client),serv,grph_str);
			return;
		}
		i++;
	}
    	my_write((*client)->fd, "ko\n");
}

void set_object(client_t **client, t_server *serv, char *str)
{
    	char *pch;
	t_tile *tiles;
	int i = 0;
	const char *stones[8] = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame","food", 0};
	char **grph_str = malloc(sizeof(char *) * 1);

	pch = strtok(str," \n");
	if (pch == NULL)
		my_write((*client)->fd,"ko\n");
	if (grph_str == NULL)
		return;
	tiles = serv->map->tiles[(*client)->position.x][(*client)->position.y];

	while (i < 7) {
		if (strcmp(pch, stones[i]) == 0 && (*client)->inventory[i] > 0) {
			tiles->stones[i] = tiles->stones[i] + 1;
			(*client)->inventory[i] = (*client)->inventory[i] - 1;
          		my_write((*client)->fd, "ok\n");
			grph_str[0] = pch;
			pdr((*client),serv,grph_str);
			return;
		}
		i++;
	}
    	my_write((*client)->fd, "ko\n");
}

