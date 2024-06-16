/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluo <hluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:58:22 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/16 11:46:13 by hluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_coredumped(int ec)
{
	if (ec == 131)
		ft_putstr_fd("Quit (core dumped)", 2);
	ft_putchar_fd('\n', 2);
}

void	close_clean_exit(t_data *d, int ec, int i)
{
	if (d->p && i != 0)
		close_pipes(d->p[i - 1]);
	close_rdr(d);
	free_n_clean(d, 1);
	exit (ec);
}

void	execve_errormsg2(t_data *d, t_com *current, int i)
{
	if (access(current->file, X_OK) != 0)
	{
		ft_putstr_fd("minishell: Permission denied: ", 2);
		if (current->args && current->args[0])
			ft_putstr_fd(current->args[0], 2);
		ft_putstr_fd("\n", 2);
		close_clean_exit(d, 126, i);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		if (current->args && current->args[0])
			ft_putstr_fd(current->args[0], 2);
		ft_putstr_fd("\n", 2);
		close_clean_exit(d, 127, i);
	}
}

void	execve_errormsg1(t_data *d, t_com *current, int i)
{
	if (current->file && (current->file[0] == '/'
			|| (current->file[0] == '.'
				&& current->file[1] == '/') || (current->file[0] == '.'
				&& current->file[1] == '.' && current->file[2] == '/'))
		&& access(current->file, F_OK) != 0)
	{
		ft_putstr_fd("minishell: No such file or directory: ", 2);
		if (current->file)
			ft_putstr_fd(current->file, 2);
		ft_putstr_fd("\n", 2);
		close_clean_exit(d, 127, i);
	}
	else if (access(current->file, F_OK) != 0)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		if (current->args && current->args[0])
			ft_putstr_fd(current->args[0], 2);
		ft_putstr_fd("\n", 2);
		close_clean_exit(d, 127, i);
	}
	execve_errormsg2(d, current, i);
}

void	get_exit_status(t_data *d, t_com *current)
{
	while (current)
	{
		waitpid(current->pid, &(current->status), 0);
		d->exit_code = current->status % 255;
		if (current->next == NULL && WIFSIGNALED(current->status) != 0)
		{
			d->exit_code = WTERMSIG(current->status) + 128;
			print_coredumped(d->exit_code);
		}
		current = current->next;
	}
}
