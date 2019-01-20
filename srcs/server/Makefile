##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Makefile, compile server and client binaries
##

SRCS_SERVER_DIR	=	.

##	SERVER SRCS	##
SRCS_SERVER	=	$(SRCS_SERVER_DIR)/main.c \
			$(SRCS_SERVER_DIR)/map.c 

##	UTILS SRCS	##
SRCS_UTILS	=	$(SRCS_UTILS_DIR)/my_write.c

OBJ_SERVER	=	$(SRCS_SERVER:.c=.o)
OBJ_UTILS	=	$(SRCS_UTILS:.c=.o)

CFLAGS		=	-W -Wall -Wextra -Werror -I../includes/

SERVER		=	zappy_server

CLIENT		=	zappy_ai

all:		$(SERVER)

$(SERVER):	$(OBJ_SERVER)
		gcc $(CFLAGS) $(OBJ_SERVER) -o $(SERVER) 

clean:
	@rm -rf $(OBJ)
	@rm -rf vgcore*

fclean:		clean
	@rm -rf $(SERVER)

re: fclean all
