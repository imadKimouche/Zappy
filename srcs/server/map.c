/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** server map
*/

#include "game.h"

#define RAND_TYPE 20
#define OBJ_MAX 4

t_tile *create_tile()
{
	t_tile *tile = malloc(sizeof(t_tile));

	if (tile == NULL)
		perror("malloc");
	for (int i = 0; i< STONE_TYPES + 1; i++) {
		tile->stones[i] = 0;
	}
	return (tile);
}

t_map *create_map(size_t x, size_t y)
{
	t_map *map = malloc(sizeof(t_map));

	if (map == NULL)
		perror("malloc");
	map->size_x = x;
	map->size_y = y;
	map->tiles = malloc(sizeof(t_tile *) * x); 
	for (size_t i = 0; i < x; i++) {
		map->tiles[i] = malloc(sizeof(t_tile) * y);
		for (size_t j = 0; j < y; j++) {
			map->tiles[i][j] = create_tile();
		}
	}
	stones_generation(map);
	food_generation(map);
	return (map);	
}

void print_tile(t_tile *tile)
{
	for (int t = 0; t < STONE_TYPES + 1; t++)
		printf(" %d", tile->stones[t]);
	printf ("\n"); 
}

void print_map(t_map *map)
{
	for (size_t i = 0; i < map->size_x; i++){
		for (size_t j = 0; j < map->size_y; j++) {
			printf("(%ld,%ld) ->", i, j);
			print_tile(map->tiles[i][j]);
		}
	}
}

void free_map(t_map *map)
{
	for (size_t i = 0; i < map->size_x; i++) {
		for (size_t j = 0; j < map->size_y; j++) {
			free(map->tiles[i][j]);
		}
		free(map->tiles[i]);
	}
	free(map);
}
