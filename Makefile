# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 16:45:04 by rwintgen          #+#    #+#              #
#    Updated: 2024/10/27 18:03:37 by rwintgen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		ircserv

CC				=		c++

FLAG			=		-Wall -Wextra -Werror -std=c++98 -g 

C_FILE			=		main.cpp					\
						Server.cpp					\
						server/commands/join.cpp	\
						server/commands/who.cpp      \
						server/commands/quit.cpp	\
						server/commands/motd.cpp	\
						server/commands/ping.cpp	\
						server/commands/mode.cpp	\
						server/commands/topic.cpp	\
						server/commands/names.cpp	\
						server/commands/part.cpp	\
						server/commands/privmsg.cpp	\
						server/commands/kick.cpp	\
						server/commands/invite.cpp	\
						server/authentication.cpp	\
						server/handleData.cpp		\
						server/utils.cpp			\
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
