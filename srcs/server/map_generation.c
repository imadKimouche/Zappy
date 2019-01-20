/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** server map generation
*/

#include "game.h"

#define RAND_TYPE 20
#define OBJ_MAX 4

void gen_in_tile(t_tile *tile, int nb_per_tile)
{
	int type;

	for (int n = 0; n < nb_per_tile; n++) {
		type = rand() % RAND_TYPE;
		if (type < STONE_TYPES) {
			tile->stones[type] += 1; 
		}
	}
}

void stones_generation(t_map *map)
{
	int nb_per_tile;

	srand(time(NULL));
	for (size_t i = 0; i < map->size_x; i++) {
		for (size_t j = 0; j < map->size_y; j++) {
			nb_per_tile = rand() % OBJ_MAX;
			gen_in_tile(map->tiles[i][j], nb_per_tile);
		}
	}
}

void food_generation(t_map *map)
{
	int nb_per_tile;

	srand(time(NULL));
	for (size_t i = 0; i < map->size_x; i++) {
		for (size_t j = 0; j < map->size_y; j++) {
			nb_per_tile = rand() % OBJ_MAX;
			map->tiles[i][j]->stones[STONE_TYPES] = nb_per_tile;
		}
	}
}
