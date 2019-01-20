/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** game server
*/

#ifndef GAME_H
#define GAME_H

#include <time.h>
#include "utils.h"

#define STONE_TYPES 6

typedef enum stones {
	linemate,
	deraumere,
	sibur,
	mendiane,
	phiras,
	thystame
} t_stone;

typedef struct s_tile {
	int stones[STONE_TYPES + 1]; // le +1 correspond à la nourriture
} t_tile;

typedef struct s_map {
	size_t size_x;
	size_t size_y;
	t_tile ***tiles;
} t_map;


t_map *create_map(size_t x, size_t y);
void stones_generation(t_map *map);
void food_generation(t_map *map);
void print_map(t_map *map);
void free_map(t_map *map);

#endif
