#include "minishell.h"

void	ft_print_echo(t_data *d, t_com *current, int i)
{
	(void) d;
	while (current && current->args && current->args[i])
	{
		ft_putstr_fd(current->args[i],STDOUT_FILENO);
		i++;
		if (current->args[i])
			write(1, " ", STDOUT_FILENO);
	}
	return ;
}

int	is_minusn(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (1);
	i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == 0)
		return (0);
	return (1);
}

void	ft_echo(t_data *d, t_com *current)
{
	int	i;

	d->exit_code = 0;
	if (!(current && current->args && current->args[0] && current->args[1]))
	{
		write(1, "\n", STDOUT_FILENO);
	}
	else if (is_minusn(current->args[1]) == 0 && current->args[2])
	{
		i = 2;
		ft_print_echo(d, current, i);
	}
	else if (is_minusn(current->args[1]) == 0)
		return ;
	else
	{
		i = 1;
		ft_print_echo(d, current, i);
		write(1, "\n", STDOUT_FILENO);
	}
}
