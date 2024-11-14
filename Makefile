# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalangi <amalangi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 16:45:04 by rwintgen          #+#    #+#              #
#    Updated: 2024/11/12 03:08:10 by amalangi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		ircserv

NAME_BONUS			=		bot

CC				=		c++

FLAG			=		-std=c++98 -g 

C_BONUS_FILE	=		Bonus/main.cpp 				\
						Bonus/handleData.cpp		\
						Bonus/Bot.cpp

C_FILE			=		main.cpp					\
						Server/Server.cpp			\
						Server/commands/join.cpp	\
						Server/commands/who.cpp		\
						Server/commands/quit.cpp	\
						Server/commands/motd.cpp	\
						Server/commands/ping.cpp	\
						Server/commands/mode.cpp	\
						Server/commands/topic.cpp	\
						Server/commands/names.cpp	\
						Server/commands/nick.cpp	\
						Server/commands/part.cpp	\
						Server/commands/privmsg.cpp	\
						Server/commands/kick.cpp	\
						Server/commands/invite.cpp	\
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

OBJ_BONUS				=		$(addprefix $(OBJ_DIR),$(C_BONUS_FILE:.cpp=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ)
	@echo "\033[0;33m\nCOMPILING FT_IRC..."
	@$(CC) $(FLAG) $(OBJ) -o $(NAME)
	@echo "\033[1;32m./$(NAME) created\n"

$(NAME_BONUS): $(OBJ_BONUS)
	@echo "\033[0;33m\nCOMPILING BOT BONUS..."
	@$(CC) $(FLAG) $(OBJ_BONUS) -o $(NAME_BONUS)
	@echo "\033[1;32m./$(NAME_BONUS) created\n"

clean:
	@echo "\033[0;31mDeleting objects..."
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;32mDone\n"

fclean: clean
	@echo "\033[0;31mDeleting executable..."
	@rm  -rf $(NAME) $(NAME_BONUS)
	@echo "\033[1;32mDone\n"

re: fclean all

.PHONY: all clean fclean re
