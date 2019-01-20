/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** string_fct
*/

#ifndef STRING_FCT_H_
	#define STRING_FCT_H_
	#include <string.h>
	#include <unistd.h>
	#include <stdlib.h>

	int my_strcmp_first_word(const char *s1, const char *s2);
	int count_words(char *str);
	char **my_str_split(char *str);
	char *my_concat(char *begin, char *to_add);
	char *re_concat(char *first, char const *second);

#endif /* !STRING_FCT_H_ */
