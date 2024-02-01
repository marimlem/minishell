#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <sys/types.h>
# include <sys/wait.h>


# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>



# include "libft/libft.h"
# include "get_next_line.h"


# define EVEN 0
# define ODD 1
# define DBLQUOTE 34
# define SGLQUOTE 39

# define BIN "/usr/bin/"



typedef struct	s_tok{
	char *tok;
	int	typ;
	struct s_tok *next;
	struct s_tok *before;

}	t_tok;

typedef struct	s_cmd{
	char *input;
	t_tok *node;
}	t_cmd;

// ft_strncmp.c
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// execute.c
void	executor(t_cmd *cmd);
void	cmd_execute(t_cmd *cmd);

// lu_inputparsing.c
void	inputparsing(t_cmd *cmd);

// lexer.c
void	lexer(t_cmd *cmd);
int	even_quotes(t_cmd *cmd);

// lexer2.c


// lex_utils.c
t_tok	*lex_lstnew(char *ptr);
int	isnot_deli(char c);
t_tok	*lex_lstlast(t_tok *lst);
void	lex_lstadd_back(t_tok **lst, t_tok *new);
void	init_list(t_cmd *cmd, char **cmd_split);
void	lst_print(t_tok *lst);

// lex_utils2.c
void	lex_lstsqueezein(t_tok *current, char *str);
void	lex_lst_rmone(t_tok *current);
char	*lex_strjoin(char const *s1, char const *s2, char deli);


#endif