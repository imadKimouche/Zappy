/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Circular_buffer
*/
#include "Circular_buffer.h"

int incr_buff(int i)
{
	i++;
	if (i == BUFF_SIZE)
		i = 0;
	return (i);
}

void read_buff(circ_buf_t *buf)
{
	int i = buf->tail;

	while (i != buf->head) {
		write(1, &(buf->buffer[i]), 1);
		i = incr_buff(i);
	}
}