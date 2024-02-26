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

# define S 32	//space
# define T 9	//tab
# define N 10	//new line

// quotes
# define DBLQUOTE 34
# define SGLQUOTE 39

# define OP -5
# define VAR -10



# define PIPE 124
# define RDR_R 62 // >
# define RDR_APP 63 // >> append
# define RDR_L 60 // <
# define RDR_DEL 61 // << delimiter

# define BIN "/usr/bin/"



// error codes
# define ERR_LEX_ALL 101
# define ERR_PAR_ALL 201
# define ERR_PAR_SYN 202
# define ERR_EXP_ALL 301


typedef struct	s_tok{
	char	*tok;
	int		typ;
	struct	s_tok *next;
	struct	s_tok *before;

}	t_tok;
typedef struct	s_var{
	char	*key;
	char	*val;
	struct	s_var *next;
}	t_var;

// if
typedef struct	s_com{
	char	*file;
	char	**args;
	char	**rdr;
	struct	s_com *next;
}	t_com;

typedef struct	s_data{
	char *input;
	t_tok *node;
	t_var *var_node;
	t_com	*com;
	int	i;
	int	q;
	int	error;
}	t_data;

// ft_strncmp.c
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// execute.c
void	executor(t_data *d);
void	d_execute(t_data *d);

// lu_inputparsing.c
void	inputparsing(t_data *d);

// lexer.c
int	lex_is_separator(char c);
void	lexer(t_data *d);
int	even_quotes(t_data *d);


// lex_utils.c
t_tok	*lex_lstnew(char *ptr);
t_tok	*lex_lstlast(t_tok *lst);
void	lex_lstadd_back(t_tok **lst, t_tok *new);
void	lst_print(t_tok *lst);
void	init_list2(t_data *d, char *input);


// lex_utils2.c
void	lex_lstsqueezein(t_tok **current, char *str);
void	lex_lst_rmone(t_tok *current);
char	*lex_strjoin(char const *s1, char const *s2, char deli);

// parser.c
void	parser(t_data *d);

// expander.c
int	is_variable(char *tok, t_var *node);
void	expand_var();
void 	expand_empty();
void 	expand_shellpid();
void	expander(t_data *d, t_tok *current);
char	*l_to_p_trans(t_data *d, t_tok *current);



#endif