NAME			=		ircserv

CC				=		c++

FLAG			=		-std=c++98 -g 

C_FILE			=		main.cpp					\
						Server.cpp					\
						Server/command/join.cpp			\
						Server/command/who.cpp			\
						Server/command/quit.cpp			\
						Server/command/motd.cpp			\
						Server/command/ping.cpp			\
						Server/authentication.cpp	\
						Server/handleData.cpp		\
						Server/utils.cpp			\
						Client.cpp					\
						Parsing.cpp					\
						Channel.cpp					\

SRC_DIR			=		./src/

INC_DIR			=		./include/

SRC				=		$(addprefix $(SRC_DIR),$(C_FILE))

OBJ				=		$(SRC:.cpp=.o)

.cpp.o:
	@$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;33m\nCOMPILING FT_IRC..."
	@$(CC) $(FLAG) $(OBJ) -o $(NAME)
	@echo "\033[1;32m./$(NAME) created\n"

clean:
	@echo "\033[0;31mDeleting objects..."
	@rm -rf $(OBJ)
	@echo "\033[1;32mDone\n"

fclean: clean
	@echo "\033[0;31mDeleting executable..."
	@rm  -rf $(NAME)
	@echo "\033[1;32mDone\n"

re: fclean all

.PHONY: all clean fclean re
