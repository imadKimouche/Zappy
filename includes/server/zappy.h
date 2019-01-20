/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Main Include
*/

#ifndef ZAPPY_H_
	#define ZAPPY_H

//	INCLUDES	//

//	MACROS		//
	#define HELP_MSG "USAGE: ./zappy_server -p port -x width -y height \
-n name1 name2 ... -c clientsNb -f freq\n \
	port		is the port number\n\
	width		is the width of the world\n\
	height		is the height of the world\n\
	nameX		is the name of the team X\n\
	clientsNB	is the number of authorized clients per team\n\
	freq		is the reciprocal of time unit for execution of action\
s\n"
//	STRUCTS		//

//	FUNCTIONS	//

//utils functions
int my_write(int fd, char *str);
#endif
