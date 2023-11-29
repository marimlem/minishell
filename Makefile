NAME = minishell

LIB_D = ./libft/
LIBFT = $(LIB_D)libft.a

SRC = main.c lu_inputparsing.c ft_strncmp.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra
CC = cc

.PHONY: all fclean re

all:	$(LIBFT) $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(OBJ):	$(SRC)
	$(CC) -c $(CFLAGS) $(SRC) -lreadline

$(LIBFT):	
	make bonus -C $(LIB_D)

clean:
	rm -f $(OBJ)
	make clean -C $(LIB_D)

fclean:	clean
	rm -f $(NAME)
	make fclean -C $(LIB_D)

re:	fclean all
