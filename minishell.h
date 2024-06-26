/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:28:48 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/19 15:09:57 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <termios.h> 
# include "libft/libft.h"

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

# define MODE_IN 1
# define MODE_IG 2
# define MODE_DF 3
# define MODE_HD 4

typedef struct s_tok
{
	char			*tok;
	int				typ;
	struct s_tok	*next;
	struct s_tok	*before;
}	t_tok;

// if
typedef struct s_com
{
	char			*file;
	char			**args;
	char			**rdr;
	int				builtin;
	__pid_t			pid;
	__pid_t			status;
	struct s_com	*next;
}	t_com;

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
	int					export_only;
}						t_envlist;

typedef struct s_data
{
	char		*input;
	t_tok		*node;
	t_com		*com;
	t_envlist	**env;
	char		**envp;
	char		**path;
	char		*tmp;
	int			i;
	int			q;
	int			error;
	int			*fd;
	int			*old_fd;
	int			heredoc_fd;
	char		*hd_path;
	int			**p;
	int			exit_code;
}	t_data;

extern int	g_signal_int;

// ft_strncmp.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// execute_builtin.c
void	execute_builtin(t_data *d, t_com *current, int ec);

// execute_heredoc.c
char	*heredoc_path(t_data *d);
void	early_heredoc(t_data *d, t_com *current);

// execute_path.c
int		setup_path(t_data *d);
int		absolut_path(t_data *d, t_com *current);
int		no_path(t_data *d, t_com *current);
int		relative_path(t_data *d, t_com *current);
int		setup_cmdpath(t_data *d);

// execute2.c
void	playground(t_data *d, t_com *current, int pc, int i);
void	process_handler(t_data *d, t_com *current, int pc, int i);
void	execute_loop(t_data *d, int pc);
void	executor2(t_data *d);
void	execute_builtin(t_data *d, t_com *current, int ec);

// execute2_utils.c
void	print_coredumped(int ec);
void	close_clean_exit(t_data *d, int ec, int i);
void	execve_errormsg2(t_data *d, t_com *current, int i);
void	execve_errormsg1(t_data *d, t_com *current, int i);
void	get_exit_status(t_data *d, t_com *current);

// execute_rdr.c
int		rdr_error(t_com *current, int error);
int		rdr_handler(t_data *d, t_com *current);

// execute_rdr_utils.c
void	close_rdr(t_data *d);
int		rdr_out(t_data *d, t_com *current, int j);
int		rdr_in(t_data *d, t_com *current, int j);
char	*heredoc_expanding(t_data *d, char *heredoc_input);
int		heredoc_start(t_data *d, t_com *current, int j);
char	*double_join(t_data *d, t_com *current, int i);

// execute_heredoc_utils.c
char	*heredoc_expanding(t_data *d, char *heredoc_input);
int		heredoc_start(t_data *d, t_com *current, int j);
int		print_heredoc_warning(void);

// execute_utils.c
int		setup_fds(t_data *d);
int		setup_pipes(t_data *d, int pipecount);
int		d_lstsize(t_com *lst);
void	close_pipes(int *tube);
void	pipe_handler(t_data *d, int pc, int i);

// init_utils.c
void	init_envlist(t_envlist **envlist);
void	init_null(t_data *d);
int		raise_shlvl(char **envp);

//list_utils.c
void	lex_lst_del(t_tok *lst);
void	com_lst_del(t_com *lst);
void	envlist_del(t_envlist *env);

// free_utils.c
void	free_n_clean(t_data *d, int b);
void	free_list(t_envlist **envlist);
void	free_double_array(char **double_array);

// signal_handling.c
void	sighdhandler(int signum);
void	sighandler(int signum);
void	signal_setup(t_data *d, int modus);
int		hd_sig_int(t_data *d, char *heredoc_input, int fd);

// lu_inputparsing.c
void	inputparsing(t_data *d);

// lexer.c
void	lexer(t_data *d);

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
int		lex_is_separator(char c);
int		even_quotes(t_data *d);

// lex_utils3.c
int		lex_sep_firstword(t_data *d, t_tok **current);
int		lex_sep_words(t_data *d, t_tok **current);
void	lex_sep_special_mid(t_data *d, t_tok **current);
int		lex_sep_special(t_data *d, t_tok **current);
int		lexer_separator(t_data *d, t_tok **current);

// parser.c
void	parser(t_data *d);

// expander.c
void	expand_empty(t_data *d, char *new);
void	expander(t_data *d, char *new, char *str);

// expander_exit.c
int		setup_ext(t_data *d, char **code, char **exp, int *len);
void	expand_exitstatus(t_data *d);
int		malloc_dat_exp(t_data *d, char **exp, char *value);

// exp_ltop.c
int		ltop_unquoter(t_data *d, char **new);
int		ltop_dollar(t_data *d, char **new, int exp);
char	*l_to_p_trans(t_data *d, char *token, int exp);

// var_handling.c
int		is_all_var(t_data *d);
void	assign_var(t_data **d);
void	rm_var(t_data *d);

// tok_types.c
void	p_op_type(t_data *d);
void	p_var(t_data *d);
void	p_syn_check(t_data *d);

// command_utils.c
int		rdr_append(t_data *d, t_tok *current, t_com *c_cur, int r);
int		arg_append(t_data *d, t_tok *current, t_com *c_cur, int a);
void	fill_com_loop(t_data *d, t_tok *current, t_com *c_cur);
void	fill_com(t_data *d, t_tok *t_node, t_com *c_node);

// command_utils2.c
t_com	*com_lstnew(void);
void	com_lstsqueezein(t_com **current);
void	init_com(t_data *d);
char	*heredoc_exp(t_data *d, char *tok, t_com *current, int r);
int		count_type(t_data *d, t_tok *t_node, int dec);

// command_utils3.c
void	alloc_coms(t_com *c_cur, int rdr_c, int arg_c);
void	setup_coms(t_data *d, t_tok *t_node, t_com *c_node);
int		fill_file_ifnecessary(t_data *d);

// add_envlist.c
int		ft_add_list(t_envlist **envlist, char *key, char *value,
			int export_check);
void	ft_print_list(t_data *d, t_envlist *envlist);
int		ft_split_first_part(char *str, char **double_array);
void	ft_split_second_part(char *str, char **double_array, int str_index);
char	**ft_eqsplit(char *str);

//split_eqsplit.c
int		ft_split_first_part(char *str, char **double_array);
void	ft_split_second_part(char *str, char **double_array, int str_index);
char	**ft_eqsplit(char *str);

//key_value_utils.c
char	*ft_find_key_value(t_envlist *envlist, const char *key);
int		ft_key_exists(t_envlist *envlist, char *key, char *value);
int		ft_key_exists_for_pe(t_envlist *envlist, char *key, char *value);
int		ft_add_key_and_value(t_envlist **envlist, char *envp, int choice);
int		ft_assign_key_and_value(t_envlist **envlist, char **envp);

//export.c
int		ft_check_arg_for_export(t_data *d, const char *s);
int		ft_check_export_input(const char *s);
void	ft_print_export(t_envlist *envlist);
int		ft_export(t_data *d, t_envlist **envlist, char **arg);

//export_utils.c
void	print_invalid_identifer(const char *s, t_data *d);
void	handle_dash(const char *s, int i, t_data *d);
void	handle_event(const char *s, t_data *d);

//unset.c
int		ft_check_arg_for_unset(const char *s);
void	ft_rm_node_front(t_envlist **envlist);
void	ft_rm_node(t_envlist **envlist, t_envlist *prev);
void	ft_unset(t_envlist **envlist, char **arg);

//is_builtin.c
int		is_builtin(t_com *current);

//cd.c
int		ft_check_driectory(t_data *d, const char *path);
void	ft_cd(t_data *d, t_com *current);

//pwd.c
int		ft_check_arg_for_pwd(t_data *d, const char *s);
void	ft_pwd(t_data *d);

//echo.c
void	ft_print_echo(t_com *current, int i);
void	ft_echo(t_data *d, t_com *current);

//exit_utils.c
void	exit_check_numeric(t_data *d, t_com *current, int ec);
void	exit_too_many_args(t_data *d);

#endif