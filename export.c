/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:55:13 by hluo              #+#    #+#             */
/*   Updated: 2024/06/13 19:08:11 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_arg_for_export(t_data *d, const char *s)
{
	int	i;

	i = 0;
	if (s[i] && !((s[i] >= 'a' && s[i] <= 'z') || \
	(s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
	{
		if (s[i] == '-')
			handle_dash(s, i, d);
		else if (s[i] == '!' && s[i + 1])
			handle_event(s, d);
		else
			print_invalid_identifer(s, d);
		return (1);
	}
	return (0);
}

int	ft_check_export_input(const char *s)
{
	int	i;

	i = 0;
	if (s[i] && ((s[i] >= 'a' && s[i] <= 'z') || \
	(s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
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
	t_envlist	*current;

	current = envlist;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd((char *)current->key, STDOUT_FILENO);
		if (current->export_only == 0)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd((char *)current->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}

int	ft_export(t_data *d, t_envlist **envlist, char **arg)
{
	int	i;
	int	err;

	err = 0;
	i = 1;
	while (arg && arg[i])
	{
		if (ft_check_export_input(arg[i]) == 1)
			err = ft_add_key_and_value(envlist, arg[i], 1);
		else if (ft_check_export_input(arg[i]) == 2)
			err = ft_add_key_and_value(envlist, arg[i], 2);
		else if (ft_check_export_input(arg[i]) == 3)
			err = ft_add_key_and_value(envlist, arg[i], 3);
		else if (ft_check_export_input(arg[i]) == 0)
		{
			d->exit_code = 1;
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd((char *)arg[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
		if (err != 0)
			return (1);
		i++;
	}
	return (0);
}
