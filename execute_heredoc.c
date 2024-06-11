/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:26:19 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 21:15:22 by lknobloc         ###   ########.fr       */
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

int	print_heredoc_warning(void)
{
	ft_putstr_fd("minishell: warning: ", 2);
	ft_putstr_fd("here-document delimited by ", 2);
	ft_putstr_fd("end-of-file instead of given delimiter\n", 2);
	return (0);
}

void	hd_loop(t_data *d, int fd, t_com *current, int j)
{
	char	*heredoc_input;

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
			return ;
		}
		if (!heredoc_input)
		{
			print_heredoc_warning();
			break ;
		}
		if (ft_strcmp(heredoc_input, current->rdr[j + 1]) == 0)
			break ;
		if (current->rdr[j][2] != SGLQUOTE)
		{
			heredoc_input = heredoc_expanding(d, heredoc_input);
			if (heredoc_input == NULL)
			{
				if (fd >= 0)
					close (fd);
				return ;
			}
		}
		ft_putstr_fd(heredoc_input, fd);
		ft_putchar_fd('\n', fd);
	}
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
		hd_loop(d, fd, current, j);
		if (fd >= 0)
			close (fd);
		j++;
		j++;
	}
}
