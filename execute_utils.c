/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:35:13 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/10 19:36:54 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_fds(t_data *d)
{
	d->old_fd = (int *) ft_calloc(sizeof(int), 3);
	if (d->old_fd == NULL)
		return (1);
	d->fd = (int *) ft_calloc(sizeof(int), 3);
	if (d->fd == NULL)
		return (1);
	d->fd[IN] = dup(STDIN_FILENO);
	d->fd[OUT] = dup(STDOUT_FILENO);
	d->old_fd[IN] = -1;
	d->old_fd[OUT] = -1;
	return (0);
}

int	setup_pipes(t_data *d, int pipecount)
{
	int	i;

	i = 0;
	d->p = (int **) ft_calloc(sizeof(int *), pipecount + 1);
	if (d->p == NULL)
		return (1);
	while (i != pipecount)
	{
		d->p[i] = (int *) ft_calloc(sizeof(int), 2);
		if (d->p[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

void	pipe_handler(t_data *d, int pc, int i)
{
	if (i != pc)
	{
		if (d->old_fd[OUT] < 0)
			dup2(d->p[i][1], STDOUT_FILENO);
		else
			dup2(d->p[i][1], d->old_fd[OUT]);
		close_pipes(d->p[i]);
	}
	if (i != 0)
	{
		if (d->old_fd[IN] < 0)
			dup2(d->p[i - 1][0], STDIN_FILENO);
		else
			dup2(d->p[i - 1][0], d->old_fd[IN]);
		close_pipes(d->p[i - 1]);
	}
}

int	d_lstsize(t_com *lst)
{
	int		i;
	t_com	*current;

	current = lst;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	close_pipes(int *tube)
{
	close (tube[0]);
	close (tube[1]);
}
