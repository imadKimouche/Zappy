/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Circular_buffer
*/

#ifndef CIRCULAR_BUFFER_H_
	#define CIRCULAR_BUFFER_H_
	#define BUFFER_SIZE 2000

	typedef struct circular_buffer_sc c_buffer;
	struct circular_buffer_sc {
		char buffer[BUFFER_SIZE];
		int head;
		int tail;
	};

#endif /* !CIRCULAR_BUFFER_H_ */
