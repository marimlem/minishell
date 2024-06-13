/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rdr_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:15:41 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/13 17:00:13 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_rdr(t_data *d)
{
	if (d->old_fd[OUT] >= 0)
	{
		dup2(d->old_fd[OUT], 1);
		close (d->old_fd[OUT]);
		// d->old_fd[OUT] = -1;
	}
	if (d->fd[OUT] >= 0)
	{
		close(d->fd[OUT]);
	}
	if (d->old_fd[IN] >= 0)
	{
		dup2(d->old_fd[IN], 0);
		close (d->old_fd[IN]);
		// d->old_fd[IN] = -1;
	}
	if (d->fd[IN] >= 0)
	{
		close(d->fd[IN]);
	}
}

void	rdr_out_open(t_data *d, t_com *current, int j)
{
	if (current->rdr[j][1] == 0)
	{
		if (d->fd[OUT] >= 0)
			close (d->fd[OUT]);
		d->fd[OUT] = open(current->rdr[j + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0744);
	}
	else
	{
		if (d->fd[OUT] >= 0)
			close (d->fd[OUT]);
		d->fd[OUT] = open(current->rdr[j + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0744);
	}
}

int	rdr_out(t_data *d, t_com *current, int j)
{
	if (d->old_fd[OUT] < 0)
		d->old_fd[OUT] = dup(STDOUT_FILENO);
	else if (d->fd[OUT] >= 0)
		close(d->fd[OUT]);
	rdr_out_open(d, current, j);
	if (d->fd[OUT] < 0)
	{
		dup2(d->old_fd[OUT], 1);
		if (d->old_fd[OUT] >= 0)
			close (d->old_fd[OUT]);
		return (j + 1);
	}
	dup2(d->fd[OUT], STDOUT_FILENO);
	return (0);
}

int	rdr_in_open(t_data *d, t_com *current, int j)
{
	if (d->fd[IN] >= 0)
		close (d->fd[IN]);
	d->fd[IN] = open(current->rdr[j + 1], O_RDONLY);
	if (d->fd[IN] < 0)
	{
		dup2(d->old_fd[IN], 0);
		if (d->old_fd[IN] >= 0)
			close (d->old_fd[IN]);
		return (j + 1);
	}
	dup2(d->fd[IN], STDIN_FILENO);
	return (0);
}

int	rdr_in(t_data *d, t_com *current, int j)
{
	if (d->old_fd[IN] < 0)
		d->old_fd[IN] = dup(STDIN_FILENO);
	else if (d->fd[IN] >= 0)
	{
		close(d->fd[IN]);
		d->fd[IN] = -1;
	}
	if (current->rdr[j][1] == '<')
	{
		if (heredoc_start(d, current, j) != 0)
			return (j + 1);
		else
			return (0);
	}
	else
	{
		if (rdr_in_open(d, current, j) == j + 1)
			return (j + 1);
	}
	return (0);
}
