#include "minishell.h"

void	ft_print_echo(t_data *d, int i)
{
	while (d->com->args[i] && ft_strcmp(d->com->args[i], "-n") != 0)
	{
		ft_putstr_fd(d->com->args[i], 2);
		i++;
		if (d->com->args[i])
			write(1, " ", 1);
	}
	return ;
}

void	ft_echo(t_data *d)
{
	int	i;

	if (ft_strcmp(d->com->args[1], "-n") == 0 && d->com->args[2])
	{
		i = 2;
		ft_print_echo(d, i);
	}
	else
	{
		i = 1;
		ft_print_echo(d, i);
		if (ft_strcmp(d->com->args[1], "-n") != 0)
			write(1, "\n", 1);
	}
}
