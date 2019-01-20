##
## EPITECH PROJECT, 2018
## myirc
## File description:
## tests
##

CC	=	gcc

CFLAGS 	=	-Wextra -Wall -Werror -I../includes/server

SRC	=	cbuff_test.c		\
		../srcs/server/cbuff.c		\
		../srcs/server/list.c		\
		../srcs/server/map.c		\
		../srcs/server/map_generation.c

OBJ	=	$(SRC:.c=.o)

all:		test

test:		$(OBJ)
		$(CC) -o test $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f test

re:		fclean all
