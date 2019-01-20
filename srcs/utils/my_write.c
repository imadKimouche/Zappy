/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** my_putstr, write a string on a fd
*/

#include <unistd.h>
#include <string.h>

int my_write(int fd, char *str)
{
	return (write(fd, str, strlen(str)));
}
