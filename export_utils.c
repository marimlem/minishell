#include "minishell.h"

void	print_invalid_identifer(const char *s, t_data *d)
{
	d->exit_code = 1;
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd((char *)s, 2);
	ft_putstr_fd(": not a valid indentifier\n", 2);
}

void	handle_dash(const char *s, int i, t_data *d)
{
	if (!s[i + 1])
	{
		d->exit_code = 1;
		ft_putstr_fd("export: `-': not a valid identifier\n", 2);
	}
	else if (s[i] == '-' && s[i + 1] == '-' && !s[i + 2])
	{
		ft_print_export(*d->env);
		return ;
	}
	else
	{
		d->exit_code = 2;
		ft_putstr_fd("export: -", 2);
		ft_putchar_fd((char)(s[i + 1]), 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
}

void	handle_event(const char *s, t_data *d)
{
	d->exit_code = 1;
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd((char *)s, 2);
	ft_putstr_fd(": event not found\n", 2);
}
