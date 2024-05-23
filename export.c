#include "minishell.h"

int	ft_check_arg_for_export(t_envlist *envlist, const char *s)
{
	int	i;

	i = 0;
	if (s[i] && !((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
	{
		if (s[i] == '-')
		{
			if (!s[i + 1])
				printf("export: `-': not a valid identifier\n");
			else if (s[i] == '-' && s[i + 1] == '-' && !s[i + 2])
			{
				ft_print_list(envlist);
				return (2);
			}
			else
				printf("export: -%c: invalid option\n", s[i + 1]);
		}
		else if (s[i] == '!')
			printf("export: %s: event not found\n", s);
		else
			printf("export: `%s': not a valid identifier\n", s);
		return (1);
	}
	return (0);
}

int	ft_check_arg_for_unset(const char *s)
{
	int	i;

	i = 0;
	if (s[i] && !((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
	{
		if (s[i] == '-' && s[i + 1] == '-' && !s[i + 2])
			return (0);
		else if (s[i] == '-' && s[i + 1])
		{
			printf("unset: -%c: invalid option\n", s[i + 1]);
		}
		else if (s[i] == '!')
			printf("unset: %s: event not found\n", s);
		return (1);
	}
	return (0);
}

int	ft_check_arg_for_pwd(const char *s)
{
	int	i;

	i = 0;
	if (s[i] && !(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z'))
	{
		if (s[i] == '-' && s[i + 1] == '-' && !s[i + 2])
			return (0);
		else if (s[i] == '-' && s[i + 1] && s[i + 1] != '-')
		{
			printf("unset: -%c: invalid option\n", s[i + 1]);
		}
		else if (s[i] == '!')
			printf("unset: %s: event not found\n", s);
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

// TODO free old value
void	ft_export(t_envlist **envlist, char **arg)
{
	int i;
	//char **export_input;

	i = 1;
	//export_input = ft_eqsplit(*arg);
	while (arg[i])
	{
		if (ft_check_export_input(arg[i]) == 1)
			ft_add_key_and_value(envlist, arg[i], 1);
		else if (ft_check_export_input(arg[i]) == 2)
			ft_add_key_and_value(envlist, arg[i], 2);
		else if (ft_check_export_input(arg[i]) == 0)
			printf("export: `%s': not a valid identifier\n", arg[i]);
		i++;
	}
}