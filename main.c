#include "minishell.h"

int	g_signal_int;

void	init_d_env(t_data **d, char **envp)
{
	*d = (t_data *) ft_calloc(1, sizeof(t_data));
	if (*d == NULL)
		return ;	
	(*d)->env = (t_envlist **)ft_calloc(1, sizeof(t_envlist *));
	if ((*d)->env == NULL)
		return ;
	*((*d)->env) = (t_envlist *)ft_calloc(1, sizeof(t_envlist));
	if ((*((*d)->env)) == NULL)
	{
		free((*d)->env);
		(*d)->env = NULL;
		return ;
	}
	init_envlist((*d)->env);
	(*d)->envp = envp;
	ft_assign_key_and_value((*d)->env, envp);
	(*d)->exit_code = 0;
	g_signal_int = 0;
	signal_setup(*d, MODE_DF);
}


int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	if (argc != 1)
		return (1);
	if (*envp == NULL || ft_strcmp(envp[0], "") == 0 || raise_shlvl(envp) != 0)
	{
		ft_putstr_fd("minishell: lol nope\n", 2);
		exit (42);
	}
	d = NULL;
	init_d_env(&d, envp);
	if (!d || !d->env || !*(d->env))
	{
		free_n_clean(d, 1);
		return (1);
	}
	while (1)
	{
		init_null(d);
		inputparsing(d);
		if (d->error != 0)
		{
			ft_putstr_fd("error: ", 2);
			ft_putnbr_fd(d->error, 2);
			ft_putstr_fd("\n", 2);
		}
		if (d->com)
			executor2(d);
		if (g_signal_int == 130)
			d->exit_code = 130;
		g_signal_int = 0;
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
