/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** network
*/
#include "Network.h"

int getProtocol(char *str)
{
	struct protoent *tcp;

	tcp = getprotobyname(str);
	if (!tcp) {
		Error(TCP_FAIL);
		exit(ERROR_EXIT);
	}
	return tcp->p_proto;
}

void create_socket(char *port, struct socket_control *sc, int protocol)
{
	int fd;

	fd = socket(AF_INET, SOCK_STREAM, protocol);
	if (fd == -1) {
		Error(SOCKET_FAIL);
		exit(ERROR_EXIT);
	}
	sc->fd = fd;
	sc->port = atoi(port);
	printf("Control Socket created\n");
}