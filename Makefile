##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Makefile, compile server and client binaries
##

SRCS_SERVER_DIR	=	./srcs/server
SRCS_CLIENT_DIR	=	./srcs/client
SRCS_UTILS_DIR	=	./srcs/utils

##	SERVER SRCS	##
SRCS_SERVER	=	$(SRCS_SERVER_DIR)/main.c 		\
			$(SRCS_SERVER_DIR)/map_generation.c 	\
			$(SRCS_SERVER_DIR)/map.c		\
			$(SRCS_SERVER_DIR)/list.c		\
			$(SRCS_SERVER_DIR)/string_fct.c		\
			$(SRCS_SERVER_DIR)/server_launch.c	\
			$(SRCS_SERVER_DIR)/annexe.c		\
			$(SRCS_SERVER_DIR)/server_run.c		\
			$(SRCS_SERVER_DIR)/Handler.c		\
			$(SRCS_SERVER_DIR)/Ia_cmd.c		\
			$(SRCS_SERVER_DIR)/cbuff.c		\
			$(SRCS_SERVER_DIR)/commands.c		\
			$(SRCS_SERVER_DIR)/tiles.c		\
			$(SRCS_SERVER_DIR)/commands2.c		\
			$(SRCS_SERVER_DIR)/commands3.c		\
			$(SRCS_SERVER_DIR)/commands4.c		\
			$(SRCS_SERVER_DIR)/send_message.c	\
			$(SRCS_SERVER_DIR)/options.c

SRCS_CLIENT 	=	$(SRCS_CLIENT_DIR)/Client.pyc		\
			$(SRCS_CLIENT_DIR)/Connections.pyc	\
			$(SRCS_CLIENT_DIR)/IA.pyc		\
			$(SRCS_CLIENT_DIR)/Utils.pyc

SRCS_CLIENT_EXE	=	$(SRCS_CLIENT_DIR)/zappy_ai.py

##	UTILS SRCS	##
SRCS_UTILS	=	$(SRCS_UTILS_DIR)/my_write.c

OBJ_SERVER	=	$(SRCS_SERVER:.c=.o)
OBJ_UTILS	=	$(SRCS_UTILS:.c=.o)

CFLAGS		=	-W -Wall -Wextra -Werror -g3 -I./includes/ -I./includes/server

SERVER		=	zappy_server

CLIENT		=	zappy_ai

all:		$(SERVER) $(CLIENT)

$(SERVER):	$(OBJ_SERVER) $(OBJ_UTILS)
		gcc $(CFLAGS) -o $(SERVER) $(OBJ_SERVER) $(OBJ_UTILS)

$(CLIENT):
		@python -m compileall ./srcs/client/
		@cp $(SRCS_CLIENT) ./
		@cp $(SRCS_CLIENT_EXE) $(CLIENT)

clean:
	@rm -rf $(OBJ_SERVER) $(OBJ_UTIL)
	@rm -rf vgcore*

fclean:		clean
	@rm -rf *.pyc
	@rm -rf $(SERVER)
	@rm -rf $(CLIENT)

re: fclean all
