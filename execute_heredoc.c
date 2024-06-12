/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:26:19 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/12 20:09:47 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_path(t_data *d)
{
	t_envlist	*node;

	node = (*d->env);
	while (node)
	{
		if (ft_strcmp(node->key, "PWD") == 0)
		{
			return (ft_strjoin(node->value, "/minishell_heredoc_tmp"));
		}
		node = node->next;
	}
	return (NULL);
}

int	hd_open_path(t_data *d)
{
	if (d->hd_path == NULL)
	{
		d->hd_path = heredoc_path(d);
		if (d->hd_path == NULL)
		{
			d->error = 1;
			return (-2);
		}
	}
	return (open(d->hd_path, O_WRONLY | O_CREAT | O_TRUNC, 0777));
}

int	hd_handle_input(t_data *d, t_com *current, char *heredoc_input, int fd)
{
	if (!heredoc_input)
	{
		print_heredoc_warning();
		return (2);
	}
	if (ft_strcmp(heredoc_input, current->rdr[d->heredoc_fd + 1]) == 0)
		return (2);
	if (current->rdr[d->heredoc_fd][2] != SGLQUOTE)
	{
		heredoc_input = heredoc_expanding(d, heredoc_input);
		if (heredoc_input == NULL)
		{
			if (fd >= 0)
				close (fd);
			return (1);
		}
	}
	return (0);
}

int	hd_loop(t_data *d, int fd, t_com *current, int j)
{
	char	*heredoc_input;
	int	var;

	d->heredoc_fd = j;
	while (1)
	{
		heredoc_input = NULL;
		signal_setup(d, MODE_HD);
		heredoc_input = readline("> ");
		signal_setup(d, MODE_DF);
		if (g_signal_int == 130)
		{
			d->exit_code = 130;
			if (fd >= 0)
				close (fd);
			return (1);
		}
		var = hd_handle_input(d, current, heredoc_input, fd);
		if (var != 0)
			return (var);
		ft_putstr_fd(heredoc_input, fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}

void	early_heredoc(t_data *d, t_com *current)
{
	int		j;
	int		fd;

	if (!current->rdr)
		return ;
	j = 0;
	while (current->rdr[j])
	{
		if (current->rdr[j][0] != '<' || current->rdr[j][1] != '<')
		{
			j++;
			j++;
			continue ;
		}
		fd = hd_open_path(d);
		if (fd < 0)
			return ;
		if (hd_loop(d, fd, current, j) != 0)
			return ;
		if (fd >= 0)
			close (fd);
		j++;
		j++;
	}
}
