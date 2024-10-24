# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 16:45:04 by rwintgen          #+#    #+#              #
#    Updated: 2024/10/24 11:09:32 by rwintgen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		ircserv

CC				=		c++

FLAG			=		-Wall -Wextra -Werror -std=c++98 -g 

C_FILE			=		main.cpp					\
						Server.cpp					\
						Server/command/join.cpp		\
						Server/command/who.cpp      \
						Server/command/quit.cpp		\
						Server/command/motd.cpp		\
						Server/command/ping.cpp		\
						Server/command/mode.cpp		\
						Server/command/topic.cpp    \
						Server/command/names.cpp	\
						Server/command/part.cpp		\
						Server/command/privmsg.cpp	\
						Server/command/kick.cpp		\
						Server/command/invite.cpp	\
						Server/authentication.cpp	\
						Server/handleData.cpp		\
						Server/utils.cpp			\
						Client.cpp					\
						Parsing.cpp					\
						Channel.cpp					\

SRC_DIR			=		./src/
INC_DIR			=		./include/
OBJ_DIR			=		./obj/

SRC				=		$(addprefix $(SRC_DIR),$(C_FILE))
OBJ				=		$(addprefix $(OBJ_DIR),$(C_FILE:.cpp=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;33m\nCOMPILING FT_IRC..."
	@$(CC) $(FLAG) $(OBJ) -o $(NAME)
	@echo "\033[1;32m./$(NAME) created\n"

clean:
	@echo "\033[0;31mDeleting objects..."
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;32mDone\n"

fclean: clean
	@echo "\033[0;31mDeleting executable..."
	@rm  -rf $(NAME)
	@echo "\033[1;32mDone\n"

re: fclean all

.PHONY: all clean fclean re
