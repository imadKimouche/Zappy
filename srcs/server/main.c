/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Zappy main function
*/

#include "./server/zappy.h"
#include "./server/game.h"
#include "./server/Server_init.h"


int main(int ac, char **av)
{
	/*if (ac < 13) {
		my_write(1, HELP_MSG);
		return (84);
	}*/
	t_server serv;
	list_t *teams = 0;
	t_option *option = parse_command_line(ac, av);

	server_init(&serv,option,&teams);
	start_server(&serv,&teams);
	return (0);
}
