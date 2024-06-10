#include "minishell.h"

void	ft_print_echo(t_com *current, int i)
{
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
	int	newline;

	d->exit_code = 0;
	i = 1;
	newline = 1;
	if (!(current && current->args))
	{
		write(1, "\n", STDOUT_FILENO);
		return ;
	}
	while (current->args[i] && is_minusn(current->args[i]) == 0)
	{
		newline = 0;
		i++;
	}
	ft_print_echo(current, i);
	if (newline)
		write(1, "\n", STDOUT_FILENO);
}
