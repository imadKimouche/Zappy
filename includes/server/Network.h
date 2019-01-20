/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Network
*/

#ifndef NETWORK_H_
	#define NETWORK_H_
	#include <sys/types.h>
       	#include <sys/socket.h>
	#include "Circular_buffer.h"
	#include "Server_init.h"
	
	int getProtocol(char *str);
//void create_socket(char *port, struct socket_control *sc, int protocol);
#endif /* !NETWORK_H_ */
