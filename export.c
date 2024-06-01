#include "minishell.h"

int	ft_check_arg_for_export(t_data *d, t_envlist *envlist, const char *s)
{
	int	i;

	i = 0;
	if (s[i] && !((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
	{
		if (s[i] == '-')
		{
			if (!s[i + 1])
			{
				d->exit_code = 1;
				ft_putstr_fd("export: `-': not a valid identifier\n", 2);
			}
			else if (s[i] == '-' && s[i + 1] == '-' && !s[i + 2])
			{
				ft_print_list(envlist);
				return (2);
			}
			else
			{
				d->exit_code = 2;
				ft_putstr_fd("export: -", 2);
				ft_putchar_fd(((char)s[i + 1]), 2);
				ft_putstr_fd(": invalid option\n", 2);
				//printf("export: -%c: invalid option\n", s[i + 1]);
			}
		}
		else if (s[i] == '!' && s[i + 1])
		{
			d->exit_code = 1;
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd((char *)s, 2);
			ft_putstr_fd(": event not found\n", 2);
			//printf("export: %s: event not found\n", s);
		}
		else
		{
			d->exit_code = 1;
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd((char *)s, 2);
			ft_putstr_fd(": not a valid indentifier\n", 2);
		}
			//printf("export: `%s': not a valid identifier\n", s);
		return (1);
	}
	return (0);
}

int	ft_check_export_input(const char *s)
{
	int	i;

	i = 0;
	if (s[i] && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
	{
		while (s[i] && ft_isalnum(s[i]) == 1)
			i++;
		if (s[i] == '=')
			return (1);
		else if (s[i] == '+' && s[i + 1] == '=')
			return (2);
		else if (!s[i])
			return (3);
	}
	return (0);
}

void	ft_print_export(t_envlist *envlist)
{
	t_envlist *current;

	current = envlist;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd((char *)current->key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd((char *)current->value, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		//printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	ft_export(t_data *d, t_envlist **envlist, char **arg)
{
	int i;

	i = 1;
	while (arg && arg[i])
	{
		if (ft_check_export_input(arg[i]) == 1)
			ft_add_key_and_value(envlist, arg[i], 1);
		else if (ft_check_export_input(arg[i]) == 2)
			ft_add_key_and_value(envlist, arg[i], 2);
		else if (ft_check_export_input(arg[i]) == 0)
		{
			d->exit_code = 1;
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd((char *)arg[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			//printf("export: `%s': not a valid identifier\n", arg[i]);
		}
		i++;
	}
}