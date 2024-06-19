/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluo <hluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:47:48 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/18 15:18:52 by hluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_within_int_range(const char *str)
{
	char	*long_max;
	char	*long_min;
	int		len;
	int		max_len;

	long_max = "9223372036854775807";
	long_min = "-9223372036854775808";
	len = ft_strlen(str);
	max_len = ft_strlen(long_max);
	if (str[0] == '-')
	{
		if (len > (max_len + 1) || (len == (max_len + 1) && ft_strcmp(str, long_min) > 0))
			return (0);
	}
	else
	{
		if (len > max_len || (len == max_len && ft_strcmp(str, long_max) > 0))
			return (0);
	}
	return (1);
}

void	exit_check_numeric(t_data *d, t_com *current, int ec)
{
	if (!is_valid_number(current->args[1]) || \
	!is_within_int_range(current->args[1]))
	{
		ec = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(current->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		close_rdr(d);
		free_n_clean(d, 1);
		exit(ec);
	}
}

void	exit_too_many_args(t_data *d)
{
	d->exit_code = 1;
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}
