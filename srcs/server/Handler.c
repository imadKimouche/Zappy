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

static const char *ct_cmd[13] = { "Forward","Right","Left", "Look", "Inventory", "Broadcast text", "Connect_nbr", "Fork", "Eject","Take", "Set", "Incantation", 0 };
static const cmd_t gui_cmd[] = {
    {"msz", 0 ,0, &msz},
    {"bct", 2, 0, &bct},
    {"mct", 0, 0, &mct},
    {"ppo", 1, 0, &player_position},
    {"plv", 1, 0, &player_level},
    {"pin", 1, 0, &player_inv},
    {"pex", 0, 0, &pex},
    {"pbc", 1, 0, &pbc},
    {"pic", 0, 0, &pic},
    {"pie", 1, 0, &pie},
    {"pdr", 1, 0, &pdr},
    {"pgt", 1, 0, &pgt},
    {"pdi", 0, 0, &pdi},
    {"seg", 0, 0, &seg},
    {"pnw", 0, 0, &new_player},
    {"tna", 0, 0, &tna},
    {NULL, 0, 0, NULL}
};
static void (*cmd_fct[13]) (client_t **client, t_server *serv, char *str) = { &forward , &right, &left, &look, &inventory, 0, &connected_usr, &fork_usr, 0, &take_object, &set_object, &incantation, 0 };

void Handler_choice(client_t **client, t_server *serv, list_t **teams)
{
	//char *str;
	(void)serv;
	(void)teams;
	char buff[BUFF_SIZE + 1];
	
	setBuffer(client);
	get_next_command(&((*client)->buf),buff);
	while (buff[0] != 0) {
		printf("Data recus : %s\n",buff);
		if ((*client)->isGraphical == 1)
			handling_Graphical(client, serv, buff);
		else if ((*client)->isGraphical == 0)
			handling_ia(client, serv, buff);
		else
			welcome_to(client,serv, buff, teams);
		get_next_command(&((*client)->buf),buff);
	}
	//free(str);
}

void handling_Graphical(client_t **client, t_server *serv, char *str)
{
	char	**tab;

	if (!(tab = my_str_split(str)))
		return ;
	for (int i = 0; gui_cmd[i].name; i++) {
	if (tab[0] && !strcmp(gui_cmd[i].name, tab[0]))
	gui_cmd[i].fun(*client, serv, tab);
	}
	free(tab);
}

void handling_ia(client_t **client, t_server *serv, char *str)
{
	int i = 0;
	char *qry;

	if (str == NULL)
		return;
	while (ct_cmd[i] != 0) {
		if ((qry = strstr(str, ct_cmd[i])) != NULL) {
			cmd_fct[i](client,serv,(qry + strlen(ct_cmd[i])));
			break;
		}
		i++;
	}
	if (ct_cmd[i] == 0)
		my_write((*client)->fd, "ko\n");

}

void setBuffer(client_t **clt)
{
	circ_buf_t *circ_buf = &((*clt)->buf);
	char buf[BUFF_SIZE];
	int *h = &(circ_buf->head);
	int t = circ_buf->tail;
	int size, read, i = 0;

	if (*h < t)
		size = (circ_buf->tail - circ_buf->head);
	else if (*h > t)
		size = (BUFF_SIZE - (*h) + t);
	else
		size = (BUFF_SIZE);
	memset(buf, 0, BUFF_SIZE);
	read = recv((*clt)->fd, buf,size, 0);
	while (read > 0 && *h != t - 1 && !(*h == BUFF_SIZE - 1 && t == 0)) {
		if (*h == BUFF_SIZE)
			*h = 0;
		circ_buf->buffer[*h] = buf[i];
		i++;
		(*h)++;
		if (*h == BUFF_SIZE)
			*h = 0;
		read--;
	}
}

int increment(int i)
{
	i++;
	if (i == BUFF_SIZE)
		i = 0;
	return (i);
}

char *read_buffer(client_t **clt)
{
	client_t *client = *clt;
	circ_buf_t *buf = &(client->buf);
	int size = 0;
	char *str;
	int i = 0;

	if (buf->tail < buf->head)
		size = buf->head - buf->tail;
	else if (buf->tail > buf->head)
		size = BUFF_SIZE - (buf->tail - buf->head);
	if (size == 0 || (str = malloc(sizeof(char) * size + 1)) == 0)
		return NULL;
	memset(str, 0, size + 1);
	while (i < size && increment(i) != client->buf.tail) {
		client->buf.tail  = increment(client->buf.tail);
		str[i] = client->buf.buffer[client->buf.tail];
		i++;
	}
	return str;
}


void get_next_command(circ_buf_t *circ, char buf[BUFF_SIZE + 1])
{
	int i = circ->tail;
	int j = 0;

	while ((circ->buffer)[i] != '\n' && i != circ->head) {
		buf[j] = circ->buffer[i];
		i = increment(i);
		j++;
	}
	buf[j] = 0;
	if ((circ->buffer)[i] != '\n' && i == circ->head &&
	    increment(circ->head) == circ->tail) {
		circ->tail = circ->head;
		return;
	}
	if ((circ->buffer)[i] != '\n' && i == circ->head) 
		buf[0] = 0;
	else if ((circ->buffer)[i] == '\n') 
		circ->tail = increment(i);
		//circ->tail = increment(circ->tail);
}


