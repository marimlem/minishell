/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluo <hluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:55:24 by hluo              #+#    #+#             */
/*   Updated: 2024/06/12 19:55:24 by hluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_handle_dash(const char *s, int i, t_data *d)
{
	if (!s[i + 1])
	{
		d->exit_code = 1;
		ft_putstr_fd("pwd: `-': not a valid identifier\n", 2);
	}
	else if (s[i] == '-' && s[i + 1] == '-' && !s[i + 2])
	{
		ft_pwd(d);
		return ;
	}
	else
	{
		d->exit_code = 2;
		ft_putstr_fd("pwd: -", 2);
		ft_putchar_fd((char)(s[i + 1]), 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
}

void	pwd_handle_event(const char *s, int i, t_data *d)
{
	if (!s[i + 1])
		return ;
	else
	{
		d->exit_code = 1;
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd((char *)s, 2);
		ft_putstr_fd(": event not found\n", 2);
	}
}

int	ft_check_arg_for_pwd(t_data *d, const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	if (s[i] && !(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z'))
	{
		if (s[i] == '-')
			pwd_handle_dash(s, i, d);
		else if (s[i] == '!')
			pwd_handle_event(s, i, d);
		return (1);
	}
	return (0);
}

void	ft_pwd(t_data *d)
{
	char	*pwd;

	pwd = (char *)ft_calloc(1, PATH_MAX);
	if (pwd == NULL)
	{
		d->exit_code = 1;
		return ;
	}
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		d->exit_code = 1;
		ft_putstr_fd("getcwd() error!\n", 2);
		free(pwd);
		return ;
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
}
