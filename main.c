#include "minishell.h"

int	g_signal_int;



int	main(int argc, char **argv, char **envp)
{
	t_data	*d;
	t_envlist	**env;

	if (argc != 1)
		return (100);

	if (*envp == NULL || ft_strcmp(envp[0], "") == 0 || raise_shlvl(envp) != 0)
	{
		ft_putstr_fd("minishell: lol nope\n", 2);
		return (1);
	}

	d = (t_data *) ft_calloc(1, sizeof(t_data));

	if (d == NULL)
		return 1;
	env = (t_envlist **)ft_calloc(1, sizeof(t_envlist *));
	if (env == NULL)
		return 1;
	*env = (t_envlist *)ft_calloc(1, sizeof(t_envlist));
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
		inputparsing(d);
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