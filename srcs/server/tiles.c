/*
** EPITECH PROJECT, 2018
** my irc
** File description:
** list management
*/

#include "tiles.h"
#include "string_fct.h"
static const char *res_m[7] = { "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "food"};

char *get_res_tiles(t_tile *tiles)
{
    char *str = malloc(sizeof(char));

    if (!str)
        return NULL;
    str[0] = '\0';
    for (int i = 0; i < (STONE_TYPES + 1); i++) {            
        for (int y = 0;y < tiles->stones[i]; y++) {
            str = re_concat(str, " ");
            str = re_concat(str, res_m[i]);
        }
    }
    return str;
}
