NAME = minishell
SRC = main.c 
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
