/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rdr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:23:15 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 18:21:28 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rdr_error(t_com *current, int error)
{
	if (error != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		if (current->rdr[error - 1][0] == '<'
			&& current->rdr[error - 1][1] == '<')
			ft_putstr_fd("heredoc error\n", 2);
		else
		{
			if (access(current->rdr[error], F_OK) == 0
				&& access(current->rdr[error], X_OK) != 0)
			{
				ft_putstr_fd(current->rdr[error], 2);
				ft_putstr_fd(": Permission denied\n", 2);
			}
			else
			{
				ft_putstr_fd(current->rdr[error], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
			}
		}
	}
	return (error);
}

int	rdr_handler(t_data *d, t_com *current)
{
	int	j;
	int	error;

	j = 0;
	error = 0;
	while (current->rdr[j])
	{
		if (current->rdr[j][0] == '>')
		{
			if (error == 0)
				error = rdr_out(d, current, j);
			else
				rdr_out(d, current, j);
		}
		else if (current->rdr[j][0] == '<')
		{
			if (error == 0)
				error = rdr_in(d, current, j);
			else
				rdr_in(d, current, j);
		}
		j = j + 2;
	}
	return (rdr_error(current, error));
}
