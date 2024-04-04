NAME = minishell

LIB_D = ./libft/
LIBFT = $(LIB_D)libft.a

SRC = main.c expander.c var_handling.c tok_types.c command_utils.c parser.c lexer.c lex_utils.c lex_utils2.c execute.c lu_inputparsing.c ft_strncmp.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra -g
CC = cc

.PHONY: all fclean re

all:	$(LIBFT) $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)


$(OBJ):	$(SRC)
	$(CC) -c $(CFLAGS) $(SRC) 
#-lreadline

$(LIBFT):	
	make bonus -C $(LIB_D)

clean:
	rm -f $(OBJ)
	make clean -C $(LIB_D)

fclean:	clean
	rm -f $(NAME)
	make fclean -C $(LIB_D)

re:	fclean all
