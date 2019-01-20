/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** string_fct
*/
#include "string_fct.h"

int my_strcmp_first_word(const char *s1, const char *s2)
{
	size_t i = 0;

	if (s1 == 0 || s2 == 0 || strlen(s1) < strlen(s2))
		return (1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (i == strlen(s2))
		return (0);
	else
		return (1);
}

char **my_str_split(char *str)
{
	char **array = NULL;
	char *pch;
	int sizetab = count_words(str);

	if (sizetab == 0)
		return (array);
	array = malloc(sizeof(char *) * (sizetab + 2));
	pch = strtok(str," :\n\r");
	for (int i = 0;pch != NULL; i++) {
		array[i] = pch;
		pch = strtok(NULL, " :\n\r");
	}
	array[sizetab + 1] = 0;
	return (array);
}

int count_words(char *str)
{
	int words = 0;
	char *pch;
	char *tmp_str = strdup(str);

	pch = strtok(tmp_str," :\n\r");
	while (pch != NULL) {
		words++;
		pch = strtok(NULL, " :\n\r");
	}
	free(tmp_str);
	return (words);
}

char	*my_concat(char *begin, char *to_add)
{
  char	*ret;

  if (!begin || !to_add)
    return (NULL);
  if (!(ret = malloc(sizeof(char) * (strlen(begin) + strlen(to_add) + 1))))
    return (NULL);
  strcpy(ret, begin);
  strcat(ret, to_add);
  free(begin);
  return (ret);
}


char *re_concat(char *first, char const *second)
{
    int size = strlen(first) + strlen(second) + 1;
    char *newBuffer;

    if (size <= 0)
        return first;
    newBuffer = malloc(sizeof(char) * size);
    if (!newBuffer)
        return first;
    strcpy(newBuffer, first);
    strcat(newBuffer, second);
    newBuffer[size - 1] = '\0';
    free(first);
    return newBuffer;
}