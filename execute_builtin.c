#include "minishell.h"

void	execute_builtin(t_data *d, t_com *current, int ec)
{
	// d->exit_code = 0;
	if (is_builtin(current) == 1) //echo
		ft_echo(d, current);
	else if (is_builtin(current) == 2) //cd
		ft_cd(d, current);
	else if (is_builtin(current) == 3) //pwd
	{
		d->exit_code = 0;
		if (!current->args[1])
			ft_pwd(d);
		else
		{
			if (ft_check_arg_for_pwd(d, current->args[1]) == 0)
				ft_pwd(d);
		}
	}
	else if (is_builtin(current) == 4) //export
	{
		d->exit_code = 0;
		if (current->args[1])
		{
			if (ft_check_arg_for_export(d, *d->env, current->args[1]) == 0)
				ft_export(d, d->env, current->args);
		}
		else
			ft_print_export(*d->env);
	}
	else if (is_builtin(current) == 5) //unset
	{
		d->exit_code = 0;
		if (current->args[1])
			if (ft_check_arg_for_unset(current->args[1]) == 0)
				ft_unset(d->env, current->args);
	}
	else if (is_builtin(current) == 6) //env
		ft_print_list(d, *d->env);
	else if (is_builtin(current) == 7) //exit
	{
		ft_putstr_fd("exit minishell\n", STDOUT_FILENO);
		if (current->args[1] == NULL)
			ec = d->exit_code;
		else if (current->args[1] != NULL && current->args[2] != NULL)
		{
			d->exit_code = 1;
			ft_putstr_fd("exit: too many arguments\n", 2);
			return ;
		}
		else
		{
			if (ft_isdigit(current->args[1][0]) == 0) 
			{
				d->exit_code = 2;
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd((char *)current->args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				return ;
			}
			else
				ec = ft_atoi(current->args[1]);

		}
		free_n_clean(d, 1);
		exit(ec) ;
	}
}