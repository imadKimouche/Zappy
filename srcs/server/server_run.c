/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** server run
*/

#include "server.h"
#include "Server_init.h"
void add_client(t_server *serv)
{
        int cs;
        struct sockaddr_in client_sin;
        socklen_t client_sin_len;

        client_sin_len = sizeof(client_sin);
        if ((cs = accept(serv->fd, (struct sockaddr *)&client_sin, &client_sin_len)) == -1) {
                perror("accept");
                return;
        }
	//serv->clients[cs].type = CLIENT;
}

void server_loop(t_server *serv)
{
	/*fd_set fd_read;
        fd_set fd_write;
        struct timeval tv;

        while (serv->is_running) {
		tv.tv_sec = 10;
                FD_ZERO(&fd_read);
                FD_ZERO(&fd_write);
                serv->fd_max = 0;
                for (int i = 0; i < serv->max_clients; i++) {
                        if (serv->clients[i].type != FREE) {
                                FD_SET(i, &fd_read);
                                FD_SET(i, &fd_write);
                                serv->fd_max = i;
                        }
                }
		if (select(serv->fd_max + 1, &fd_read, NULL, NULL, &tv) == -1)
                        perror("select");
		if (FD_ISSET(serv->fd, &fd_read)) {
			add_client(serv);
		}
		for (int i = 0; i < serv->max_clients; i++) {			
			if (i != serv->fd && FD_ISSET(i, &fd_read)) {
				// traitement de la commande
			}
		}
	}*/
        (void)serv;
}
