#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <fcntl.h>

# include <sys/types.h>
# include <sys/wait.h>


# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>



# include "libft/libft.h"
# include "get_next_line.h"


# define EVEN 0
# define ODD 1

# define IN 0
# define OUT 1

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
	__pid_t		pid;
	__pid_t		status;
	struct	s_com *next;
}	t_com;

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}						t_envlist;

typedef struct	s_data{
	char *input;
	t_tok *node;
	t_var *var_node;
	t_com	*com;
	t_envlist	**env;
	char	**path;
	char	*tmp;
	int	i;
	int	q;
	int	error;
	int	*fd;
	int	*old_fd;
	int	heredoc_fd;
	int	**p;
	// __pid_t	pid;
	// __pid_t	status;
}	t_data;

// ft_strncmp.c
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// execute.c
// void	executor(t_data *d);
// void	d_execute(t_data *d);

// execute2.c
void	pipe_handler(t_data *d, int pc, int i);
void	playground(t_data *d, t_com *current ,int pc, int i);
void	process_handler(t_data *d, t_com *current, int pc, int i);
void	execute_loop(t_data *d, int pc);
void	executor2(t_data *d);

// execute_rdr.c
void	close_rdr(t_data *d);
int	rdr_out(t_data *d, t_com *current, int j);
int	rdr_in(t_data *d, t_com *current, int j);
int	heredoc_start(t_data *d, t_com *current, int j);
int	rdr_handler(t_data *d, t_com *current);



// execute_utils.c
int	setup_fds(t_data *d);
int	setup_pipes(t_data *d, int pipecount);
int	d_lstsize(t_com *lst);
void	close_pipes(int *tube);



// lu_inputparsing.c
void	inputparsing(t_data *d, t_envlist **envlist);

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


// main.c
void	free_n_clean(t_data *d, int b);

// parser.c
void	parser(t_data *d);

// expander.c
int	is_variable(t_var *node, char *find);
void	expand_var();
void 	expand_empty(t_data *d, char *new);
void 	expand_shellpid();
void	expander(t_data *d, char *new, char *str);
char	*l_to_p_trans(t_data *d, char *token, int exp);

// var_handling.c
int	is_all_var(t_data *d);
t_var	*var_lst_new();
void	assign_var(t_data **d);
void	rm_var(t_data *d);

// tok_types.c
void	p_op_type(t_data *d);
void	p_var(t_data *d);
void	p_syn_check(t_data *d);

// command_utils.c
t_com	*com_lstnew();
void	com_lstsqueezein(t_com **current);
void	init_com(t_data *d);
void	fill_com(t_data *d, t_tok *t_node, t_com *c_node);

// env_utils.c
int	ft_contains_char(const char *s, char c);
void	ft_add_list(t_envlist **envlist, char *key, char *value);
void	ft_print_list(t_envlist *envlist);
int	ft_split_first_part(char *str, char **double_array);
void	ft_split_second_part(char *str, char **double_array, int str_index);
char	**ft_eqsplit(char *str);

//key_value_utils.c
char	*ft_find_key_value(t_envlist *envlist, const char *key);
int	ft_key_exists(t_envlist *envlist, char *key, char *value);
int	ft_key_exists_for_PE(t_envlist *envlist, char *key, char *value);
void	ft_add_key_and_value(t_envlist **envlist, char *envp, int choice);
void	ft_assign_key_and_value(t_envlist **envlist, char **envp);

#endif