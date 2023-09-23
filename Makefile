NAME = minishell
SRC = main.c lu_inputparsing.c ft_strncmp.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:%.c=%.o)
CFLAGS = -Wall -Werror -Wextra
CC = cc

.PHONY: all fclean re

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ):	$(SRC)
	$(CC) -c $(CFLAGS) $(SRC) 

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
