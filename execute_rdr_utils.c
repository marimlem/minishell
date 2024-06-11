/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rdr_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:15:41 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 18:15:42 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_rdr(t_data *d)
{
	if (d->old_fd[OUT] >= 0)
	{
		dup2(d->old_fd[OUT], 1);
		if (d->fd[OUT] >= 0)
			close(d->fd[OUT]);
	}
	if (d->old_fd[IN] >= 0)
	{
		dup2(d->old_fd[IN], 0);
		if (d->fd[IN] >= 0)
			close(d->fd[IN]);
	}
}

int	rdr_out(t_data *d, t_com *current, int j)
{
	if (d->old_fd[OUT] < 0)
		d->old_fd[OUT] = dup(STDOUT_FILENO);
	else if (d->fd[OUT] >= 0)
		close(d->fd[OUT]);
	if (current->rdr[j][1] == 0)
		d->fd[OUT] = open(current->rdr[j + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0744);
	else
		d->fd[OUT] = open(current->rdr[j + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (d->fd[OUT] < 0)
	{
		dup2(d->old_fd[OUT], 1);
		return (j + 1);
	}
	dup2(d->fd[OUT], STDOUT_FILENO);
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
		d->fd[IN] = open(current->rdr[j + 1], O_RDONLY);
		if (d->fd[IN] < 0)
		{
			dup2(d->old_fd[IN], 0);
			return (j + 1);
		}
		dup2(d->fd[IN], STDIN_FILENO);
	}
	return (0);
}

char	*heredoc_expanding(t_data *d, char *heredoc_input)
{
	d->i = 0;
	if (heredoc_input == NULL || heredoc_input[d->i] == 0)
		return (heredoc_input);
	while (heredoc_input[d->i])
	{
		if (heredoc_input[d->i] == '$')
		{
			d->tmp = heredoc_input;
			expander(d, &heredoc_input[d->i], heredoc_input);
			heredoc_input = d->tmp;
			d->tmp = NULL;
			continue ;
		}
		d->i++;
	}
	return (heredoc_input);
}

int	heredoc_start(t_data *d, t_com *current, int j)
{
	(void) current;
	(void) j;
	if (d->old_fd[IN] != -1)
		dup2(d->old_fd[IN], 0);
	d->fd[IN] = open(d->hd_path, O_RDONLY | O_CREAT, 0744);
	if (d->fd[IN] < 0)
		return (d->heredoc_fd + 1);
	dup2(d->fd[IN], STDIN_FILENO);
	return (0);
}
