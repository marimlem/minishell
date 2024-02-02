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
# define PIPE 124
# define RDR_R 62 // >
# define RDR_APP 63 // >> append
# define RDR_L 60 // <
# define RDR_DEL 61 // << delimiter


# define BIN "/usr/bin/"


typedef struct	s_tok{
	char *tok;
	int	typ;
	struct s_tok *next;
	struct s_tok *before;

}	t_tok;

typedef struct	s_data{
	char *input;
	t_tok *node;
	int	i;
	int	q;
}	t_data;

// ft_strncmp.c
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// execute.c
void	executor(t_data *d);
void	d_execute(t_data *d);

// lu_inputparsing.c
void	inputparsing(t_data *d);

// lexer.c
void	lexer(t_data *d);
int	even_quotes(t_data *d);

// lexer2.c
void	quote_merge_2(t_data *d);


// lex_utils.c
t_tok	*lex_lstnew(char *ptr);
int	isnot_deli(char c);
t_tok	*lex_lstlast(t_tok *lst);
void	lex_lstadd_back(t_tok **lst, t_tok *new);
void	init_list(t_data *d, char **d_split);
void	lst_print(t_tok *lst);

// lex_utils2.c
void	lex_lstsqueezein(t_tok *current, char *str);
void	lex_lst_rmone(t_tok *current);
char	*lex_strjoin(char const *s1, char const *s2, char deli);


#endif