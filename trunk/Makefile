##
## Makefile for my_ftp in /u/all/milbau_a/cu/rendu/c/my_ftp2
## 
## Made by alexis milbault
## Login   <milbau_a@epitech.net>
## 
## Started on  Wed Apr 14 17:36:07 2010 alexis milbault
## Last update Sun Jun 20 16:08:28 2010 alexandra ekra
##

NAME		=	serveur
NAME2		=	client

SRC_SERVER	=	src_server/main.c			\
			src_server/get_arg.c			\
			src_server/get_params.c			\
			src_server/do_server.c			\
			src_server/client_management.c		\
			src_server/select_team.c		\
			src_server/gestion_timer.c		\
			src_server/init_map.c			\
			src_server/map_func.c			\
			src_server/action_move.c		\
			src_server/action_see.c			\
			src_server/action_objects.c		\
			src_server/commande_management.c	\
			src_server/init_client.c		\
			src_server/elem_timer.c			\
			src_server/annexe.c			\
			src_server/print_func.c			\
			src_server/action_others.c		\
			src_server/msg_to_graph1.c		\
			src_server/ghost_mode.c			\
			src_server/client_state.c		\
			src_server/graph_commands.c		\
			src_server/send_cases_content.c		\
			src_server/send_player_info.c		\
			src_server/graph_commands_player.c	\
			src_server/graph_commands_cases.c	\


SRC_COMMON	=	common/utils.c 			\
			common/xfunc.c			\
			common/check_func.c		\
			common/utils_2.c		\
			common/my_str_to_wordtab.c	\

SRC_CLIENT	=	src_client/main.c 		\

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)
OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)
OBJ_COMMON	=	$(SRC_COMMON:.c=.o)

CC		=	gcc


INCLUDE		=	-I./includes
CFLAGS		+=	$(INCLCUDE) -W -Wall -pedantic -ansi -g3

RM		=	rm -f


all: 	$(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_COMMON)
	@echo -e "\033[31m=== Server compilation ===\033[00m"
	$(CC) -o $(NAME) $(OBJ_SERVER) $(OBJ_COMMON) $(CFLAGS)
	@echo -e $(SRC_SERVER) "\033[32m==> Compilation sucess\033[00m"
	@echo -e "\033[31m=== Client compilation ===\033[00m"
	$(CC) -o $(NAME2) $(OBJ_CLIENT) $(OBJ_COMMON) $(CFLAGS)
	@echo -e $(SRC_CLIENT) $(OBJ_COMMON) "\033[32m==> Compilation sucess\033[00m"

clean:
	clean
	@echo -e "\033[31m=== Clean mode ===\033[00m"
	@$(RM) $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_COMMON)
	@echo -e $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_COMMON) "\033[32m==> Delete sucess\033[00m"

fclean:	clean
	@$(RM) $(NAME) $(NAME2) *# */*#
	@echo -e $(NAME) $(NAME2) "\033[32m==> EXE delete sucess\033[00m"

re:		fclean all

.PHONY:		all re clean fclean

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@