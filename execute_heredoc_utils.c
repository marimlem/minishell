/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:52:57 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/12 18:52:58 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
