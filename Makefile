NAME = minishell

LIB_D = ./libft/
LIBFT = $(LIB_D)libft.a

SRC = main.c \
	expander.c exp_ltop.c tok_types.c command_utils.c parser.c lexer.c lex_utils.c lex_utils2.c lex_utils3.c \
	init_utils.c signal_handling.c list_utils.c free_utils.c\
	lu_inputparsing.c ft_strncmp.c \
	execute2.c execute_utils.c execute_rdr.c execute_builtin.c execute_heredoc.c execute_path.c \
	add_envlist.c key_value_utils.c export.c unset.c is_builtin.c \
	cd.c pwd.c echo.c split_eqsplit.c exit_utils.c export_utils.c \
	command_utils2.c command_utils3.c expander_exit.c execute_rdr_utils.c \
	execute_heredoc_utils.c execute2_utils.c

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

v:
	valgrind --suppressions=supp.supp --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

clean:
	rm -f $(OBJ)
	make clean -C $(LIB_D)

fclean:	clean
	rm -f $(NAME)
	make fclean -C $(LIB_D)

re:	fclean all
