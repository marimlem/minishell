#include "minishell.h"

void	ft_print_echo(t_data *d, t_com *current, int i)
{
	(void) d;
	while (current->args[i] && ft_strcmp(current->args[i], "-n") != 0)
	{
		ft_putstr_fd(current->args[i],STDOUT_FILENO);
		i++;
		if (current->args[i])
			write(1, " ", 1);
	}
	return ;
}

void	ft_echo(t_data *d, t_com *current)
{
	int	i;
	if (!(current && current->args && current->args[0] && current->args[1]))
	{
		write(1, "\n", STDOUT_FILENO);
	}
	else if (ft_strcmp(current->args[1], "-n") == 0 && current->args[2])
	{
		i = 2;
		ft_print_echo(d, current, i);
	}
	else
	{
		i = 1;
		ft_print_echo(d, current, i);
		write(1, "\n", STDOUT_FILENO);
	}
}
