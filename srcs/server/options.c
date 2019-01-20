/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** commandline options
*/

#include "server.h"
#include "list.h"
#include "zappy.h"

void add_teams(t_option *opt, int argc, char *argv[])
{
	t_team *t = malloc(sizeof(t_team));

	t->name = optarg;
	t->current_user = 0;
	t->max_client = 2; //AJOUTER ICI LE NOMBRE MAX DE CLIENT
	t->client = 0;
	
	my_add_data(&(opt->teams), t);
	while (optind < argc && argv[optind][0] != '-' && (t = malloc(sizeof(t_team)))) {
		t->name = argv[optind++];
        	t->current_user = 0;
        	t->max_client = 2; //AJOUTER ICI LE NOMBRE MAX DE CLIENT
        	t->client = 0;
		my_add_data(&(opt->teams), t);
	}
}

t_option *init_options()
{
	t_option *option = malloc(sizeof(t_option));

	if (option == NULL) {
		my_write(2, "Couldn't malloc");
		exit(EXIT_FAILURE);
	}
	option->port = -1;
	option->x = -1;
	option->y = -1;
	option->teams = NULL;
	option->max_clients = -1;
	option->freq = -1;
	return (option);
}

int check_options(t_option *option)
{
	int res = 0;
	if (option->port < 0) {
		my_write(2, "port must be given and must be positive\n");
		res++;
	}
	if (option->x < 0) {
		my_write(2, "height must be given and must be positive\n");
		res++;
	}
	if (option->y < 0) {
		my_write(2, "width must be given and must be positive\n");
		res++;
	}
	if (option->max_clients < 0) {
		my_write(2, "max_client per team must be given and must be positive\n");
		res++;
	}
	if (option->freq < 0) {
		my_write(2, "frequency must be given and must be positive\n");
		res++;
	}
	if (my_list_size(option->teams) < 2) {
		my_write(2, "you must give more than 1 team\n");
		res++;
	}
	return (res == 0 ? 0 : -1);
}

t_option *parse_command_line(int argc, char **argv)
{
	char c;
	t_option *opt = init_options();

	while ((c = getopt(argc, argv, "p:x:y:c:n:f:")) != -1) {
		switch(c) {
			case 'p':
			opt->port = atoi(optarg);
			break;
			case 'x':
			opt->x = atoi(optarg);
			break;
			case 'y':
			opt->y = atoi(optarg);
			break;
			case 'c':
			opt->max_clients = atoi(optarg);
			break;
			case 'f':
			opt->freq = atoi(optarg);
			break;
			case 'n':
			add_teams(opt, argc, argv);
			break;
		}
	}
	add_team_max_client(opt->max_clients,&(opt->teams));
	if (check_options(opt) != 0) {
		my_write(2, HELP_MSG);
		exit(EXIT_FAILURE);
	}

	return(opt);
}

void add_team_max_client(int maxclient, list_t **teams_list)
{
	list_t *tmp = *teams_list;
	t_team *node;

	while (tmp != NULL) {
		node = (t_team *)tmp->data;
		if (node != 0 && maxclient > 0){
			node->max_client = maxclient;
		}
		tmp = tmp->next;
	}
}