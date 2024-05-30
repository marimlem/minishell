#include "minishell.h"

int	g_signal_int;

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
void	lex_lst_del(t_tok *lst)
{
	t_tok	*c;

	c = lst;
	if (c)
	{
		lex_lst_del(c->next);
		if (c->tok)
			free (c->tok); //invalid free
		c->next = NULL;
		free (c);
	}

}
void	com_lst_del(t_com *lst)
{
	t_com	*c;
	int	i;

	i = 0;
	c = lst;
	if (c)
	{
		com_lst_del(c->next);
		if (c->file)
			free (c->file);
		c->file = NULL;
		if (c->args)
		{
			while (c->args[i])
			{
				free (c->args[i]);
				c->args[i++] = NULL;
			}
			free (c->args);
			c->args = NULL;
		}
		i = 0;
		if (c->rdr)
		{
			while (c->rdr[i])
			{
				free (c->rdr[i]);
				c->rdr[i++] = NULL;
			}
			free (c->rdr);
			c->rdr = NULL;
		}
		c->next = NULL;
		free (c);

	}

}

void	envlist_del(t_envlist *env)
{
	t_envlist *e;

	e = env;
	if (e)
	{
		envlist_del(e->next);
		if (e->key)
			free (e->key);
		e->key = NULL;
		if (e->value)
			free (e->value);
		e->value = NULL;
		e->next = NULL;
		free (e);
	}
}
void    free_list(t_envlist *envlist)
{
    t_envlist    *temp;
    t_envlist    *temp2;

	if (!envlist)
		return ;
	temp = envlist;
    while (temp)
    {
        free(temp->key);
        free(temp->value);
        temp2 = temp->next;
        free(temp);
		temp = NULL;
		temp = temp2;
		temp2 = NULL;
    }
    // free(envlist);
}

void	free_n_clean(t_data *d, int b)
{
	int	i;

	i = 0;
	
	lex_lst_del(d->node);
	com_lst_del(d->com);
	
	if (d->input)
		free (d->input);
	// if (d->node)
		// free (d->node);
	// if (d->com)
		// free (d->com);
	if (d->tmp)
		free (d->tmp);
	d->error = 0;
	d->i = 0;
	d->q = 0;
	if (d->fd)
		free (d->fd);
	if (d->old_fd)
		free(d->old_fd);
	if (d->path)
	{
		while (d->path[i])
		{
			free(d->path[i]);
			d->path[i++] = NULL;
		}
		free (d->path);
	}

	i = 0;
	if (d->p)
	{
		while (d->p[i])
		{
			free (d->p[i]);
			d->p[i++] = NULL;
		}
		free (d->p);
		d->p = NULL;
	}
	if (d->hd_path)
	{
		unlink(d->hd_path);
		free (d->hd_path);
	}

	if (b == 0)
		return ;
	if (d->env)
	{
		free_list	(*(d->env));
		// free (d->env);
	}
	if (d)
		free (d);
	d = NULL;
	

}

void	init_envlist(t_envlist **envlist)
{
	(*envlist)->key = NULL;
	(*envlist)->value = NULL;
	(*envlist)->next = NULL;
}

void	init_null(t_data *d)
{
	d->input = NULL;
	d->node = NULL;
	d->com = NULL;
	d->tmp = NULL;
	d->var_node = NULL;
	d->fd = NULL;
	d->old_fd = NULL;
	d->i = 0;
	d->q = 0;
	d->error = 0;
	d->p = NULL;
	d->path = NULL;
	d->hd_path = NULL;
	// d->p[0] = 0;
	// d->p[1] = 0;
	d = NULL;
	
}

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		signal(SIGINT, sighandler);
		if (g_signal_int == 2)
		{
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
			g_signal_int = 3;
			rl_replace_line("", 0);
			rl_on_new_line();	
			return ;
		}
		else
		{

			ft_putchar_fd('\n', 2);
			// ioctl(STDIN_FILENO, TIOCSTI, "\n");

			g_signal_int = 1;
			rl_replace_line("", 0);
			rl_on_new_line();	
			rl_redisplay();
		}
	}
	// else if (signum == SIGQUIT)
	// {
	// 	signal(SIGQUIT, sighandler);

	// 	rl_on_new_line();	
	// 	rl_redisplay();
	// 	rl_replace_line("", 0);
	// 	return ;
	// }
	(void) signum;
	return ;
}


void	signal_setup(t_data *d, int modus)
{
	(void) d;
	
	if (modus == MODE_IN)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (modus == MODE_IG)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (modus == MODE_DF)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	// else if (modus == MODE_HEDOC)
	// {

	// }





	// setvbuf(stdout,NULL,_IONBF,0);

/* 	struct termios old_termios, new_termios;
	tcgetattr(0,&old_termios);

	signal( SIGINT, sig_hnd );

	new_termios             = old_termios;
	new_termios.c_cc[VEOF]  = 3; // ^C
	new_termios.c_cc[VINTR] = 4; // ^D
	tcsetattr(0,TCSANOW,&new_termios);
	tcsetattr(0,TCSANOW,&old_termios);

 	 //tcsetattr(0,TCSANOW,&old_termios);
 */
}

int	raise_shlvl(char **envp)
{
	int	i;
	int	lvl;

	i = 0;
	lvl = -1;
	while(envp && envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			lvl = ft_atoi(&envp[i][6]);
			// printf("lvl: %s\n", d->envp[i]);
			if (lvl >= 9)
			{
				ft_putstr_fd("minishell error: shell-level too high: ", 2);
				ft_putnbr_fd(lvl, 2);
				ft_putstr_fd("\n", 2);
				return (lvl);
			}
			else
			{
				envp[i][6] = envp[i][6] + 1;
			}
			break ;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;
	t_envlist	**env;

	if (argc != 1)
		return (100);
	if (raise_shlvl(envp) != 0)
	{
		return (1);
	}
	d = (t_data *) malloc(sizeof(t_data) * 1);
	if (d == NULL)
		return 1;
	env = (t_envlist **)malloc(sizeof(t_envlist *));
	if (env == NULL)
		return 1;
	*env = (t_envlist *)malloc(sizeof(t_envlist));
	if ((*env) == NULL)
	{
		free(env);
		return 1;
	}
	init_envlist(env);
	d->envp = envp;
	ft_assign_key_and_value(env, envp);
	d->env = env;
	d->exit_code = 0;
	g_signal_int = 0;

	signal_setup(d, MODE_DF);
	while (1)
	{
		init_null(d);
		inputparsing(d, env);
		if (d->error == -1)
		{
			// ft_putstr_fd("exit minishell\n", 2);
			break ;
		}
		if (d->error != 0)
		{
			ft_putstr_fd("error: ", 2);
			ft_putnbr_fd(d->error, 2);
			ft_putstr_fd("\n", 2);
		}
		// if list is completely variable assignment type, assign variables, else go to executor
		if (d->com && d->com->file && d->com->file[0] != 0)
			executor2(d);
		
		free_n_clean(d, 0);
	}
	if (d->var_node)
		free (d->var_node);
	d->var_node = NULL;
	free_n_clean(d, 1);
	(void) argv;
	// (void) command;
	return (0);
} 