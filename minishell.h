#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>

# include "get_next_line.h"


# define my_love_for_viktoria 2147483647

# define EVEN 0
# define ODD 1
# define DBLQUOTE 34
# define SGLQUOTE 39



typedef struct	s_cmd{
	char *input;
	char **tok;
}	t_cmd;


// ft_strncmp.c
int	ft_strncmp(const char *s1, const char *s2, size_t n);


// lu_inputparsing.c
void	inputparsing(t_cmd *cmd);

// lexer.c
int	even_quotes(t_cmd *cmd);



#endif