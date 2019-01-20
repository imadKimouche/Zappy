/*
** EPITECH PROJECT, 2018
** my irc
** File description:
** circular buffer gestion
*/

#include "utils.h"

t_cbuff *create_buff(size_t size)
{
	t_cbuff *buff = malloc(sizeof(*buff));

	if (buff == NULL) {
		perror("malloc");
	}
	buff->head = 0;
	buff->tail = 0;
	buff->size = size;
	if ((buff->buff = malloc(sizeof(char) * (size+1))) == NULL) {
		free(buff);
		perror("malloc");
	}
	buff->buff[size] = 0;
	buff->empty = 1;
	memset(buff->buff, 0, size);
	return (buff);
}

void reset_buff(t_cbuff *buff)
{
	if (buff) {
		buff->tail = 0;
		buff->head = 0;
		buff->empty = 1;
	}
}

char *read_buff(t_cbuff *buff)
{
	size_t len;
	char *str = NULL;
	
	if (buff == NULL || buff->empty)
		return (NULL);
	if (buff->tail > buff->head) {
		len = buff->tail - buff->head;
		if ((str = malloc(sizeof(char) * (len + 1))) == NULL)
		    perror("malloc");
		memcpy(str, buff->buff + buff->head, len);
		str[len] = 0;
	} else if (buff->tail < buff->head) {
		len = buff->size - buff->head;
		if ((str = malloc(sizeof(char) * (len + buff->tail + 1))) == NULL)
		    perror("malloc");
		memcpy(str, buff->buff + buff->head, len);
		memcpy(str + len, buff->buff, buff->tail);
		str[len + buff->tail] = 0;
	}
	buff->empty = 1;
	return (str);
}

void write_buff(t_cbuff *buff, char *str)
{
	size_t len = strlen(str);

	if (buff == NULL || buff->size < len )
	        perror("write buffer");
	buff->head = buff->tail;
        if (buff->size < buff->tail + len) {
		len = buff->size - buff->tail;
		memcpy(buff->buff + buff->tail, str, len);
		buff->tail = 0;
		str = str + len;
		len = strlen(str);
	}
	memcpy(buff->buff + buff->tail, str, len);
	buff->tail = buff->tail + len;
	buff->empty = 0;
}
