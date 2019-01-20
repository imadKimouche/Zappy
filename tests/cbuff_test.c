/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** tests for list
*/

#include "../includes/server/utils.h"
#include "../includes/server/game.h"


typedef int(*fct)();

void test(fct func, char *name)
{
	int res;
	printf("Test %s : ", name);
	if ((res = func()) == 0) {
		printf("OK\n");
	} else {
		printf("KO %d errors\n", res);
	}
}

int test_list_add(void)
{
	t_list *list = create_list();
	int a = 20;
	int b = 10;
	int c = 5;
	int res = 0;

	add_elem(&list, &a);
	if (*(int *)list->data != 20)
		res++;
	add_elem(&list, &b);
	if (*(int *)list->data != 10 || *(int *)list->next->data != 20
	    || *(int *)list->next->prev->data != 10)
		res++;
	add_elem(&list, &c);
	if (*(int *)list->next->data != 10
	    || *(int *)list->next->next->data != 20
	    || *(int *)list->next->prev->data != 5)
		res++;
	return (res);
}

int test_list_remove(void)
{
	t_list *list = create_list();
	int a = 20;
	int b = 10;
	int c = 5;
	int res = 0;

	add_elem(&list, &a);
	add_elem(&list, &b);
	add_elem(&list, &c);
	remove_elem(list->next);
	if (*(int *)list->data != 5 || *(int *)list->next->data != 20
	    || *(int *)list->next->prev->data != 5) {
		res++;
	}
	return (res);
}

int buff_test_write(void)
{
	int res = 0;
	t_cbuff *buff = create_buff(24);

	write_buff(buff, "hello world");	
	res = strcmp(buff->buff, "hello world");
	write_buff(buff, " goodbye");
	res = strcmp(buff->buff, "hello world goodbye");
	write_buff(buff, "123456");
	res = strcmp(buff->buff, "6ello world goodbye12345");	
	return (res);
}

int test_buff_read(void)
{
	int res = 0;
	t_cbuff *buff = create_buff(24);
	char *str;

	write_buff(buff, "hello world");
	str = read_buff(buff);
	res = strcmp(str, "hello world");
	write_buff(buff, "goodbye");
	free(str);
	str = read_buff(buff);
	res = strcmp(str, "goodbye");
	write_buff(buff, "bonjour il fait beau");
	free(str);
	str = read_buff(buff);
	res = strcmp(str, "bonjour il fait beau");
	free(str);
	return (res);
}

int test_buff_write_read()
{
	int res = 0;
	t_cbuff *buff = create_buff(24);
	char *str;

	write_buff(buff, "hello world");
	str = read_buff(buff);
	free(str);
	str = read_buff(buff);
	res = str == NULL ? 0 : 1;
	free(str);
	return (res);
}

int main(void)
{
	/*test(test_list_add, "list_add");
	test(test_list_remove, "list_remove");
	test(buff_test_write, "buff write");
	test(test_buff_read, "buff read");
	test(test_buff_write_read, "buff read write");*/

	t_map *map = create_map(5, 10);

	printf ("test map\n");
	print_map(map);
	free_map(map);
	return (0);
}
