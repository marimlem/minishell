#include "minishell.h"

void	handle_pwd(t_data *d, t_com *current)
{
	d->exit_code = 0;
	if (current->args[1] == NULL)
		ft_pwd(d);
	else
	{
		if (ft_check_arg_for_pwd(d, current->args[1]) == 0)
			ft_pwd(d);
	}
}

void	handle_export(t_data *d, t_com *current)
{
	d->exit_code = 0;
	if (current->args[1] != NULL)
	{
		if (ft_check_arg_for_export(d, current->args[1]) == 0)
			ft_export(d, d->env, current->args);
	}
	else
		ft_print_export(*d->env);
}

void	handle_unset(t_data *d, t_com *current)
{
	d->exit_code = 0;
	if (current->args[1] != NULL)
		if (ft_check_arg_for_unset(current->args[1]) == 0)
			ft_unset(d->env, current->args);
}

void	handle_exit(t_data *d, t_com *current, int ec)
{
	int i = 0;	
	ft_putstr_fd("exit minishell\n", STDOUT_FILENO);
	if (current->args[1] == NULL)
		ec = d->exit_code;
	else
	{
		while (current->args[1][i])
		{
			exit_check_numeric(d, current, ec, i);
			i++;
		}
		if (current->args[2] != NULL)
			exit_too_many_args(d);
		ec = ft_atoi(current->args[1]);
	}
	free_n_clean(d, 1);
	exit(ec);
}

void	execute_builtin(t_data *d, t_com *current, int ec)
{
	int builtin_id;

	builtin_id = is_builtin(current);
	if (builtin_id == 1)
		ft_echo(d, current);
	else if (builtin_id == 2)
		ft_cd(d, current);
	else if (builtin_id == 3)
		handle_pwd(d, current);
	else if (builtin_id == 4)
		handle_export(d, current);
	else if (builtin_id == 5)
		handle_unset(d, current);
	else if (builtin_id == 6)
		ft_print_list(d, *d->env);
	else if (builtin_id == 7)
		handle_exit(d, current, ec);
}
