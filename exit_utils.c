#include "minishell.h"

void	exit_check_numeric(t_data *d, t_com *current, int ec, int i)
{
	if (!ft_isdigit(current->args[1][i]) && \
	(i != 0 || current->args[1][i] != '-'))
	{
		ec = 2;
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(current->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_n_clean(d, 1);
		exit(ec);
	}
}

void	exit_too_many_args(t_data *d)
{
	d->exit_code = 1;
	ft_putstr_fd("exit: too many arguments\n", 2);
	return ;
}
