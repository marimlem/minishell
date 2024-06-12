/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:58:22 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/12 19:47:17 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_coredumped(int ec)
{
	if (ec == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	close_clean_exit(t_data *d, int ec)
{
	close_rdr(d);
	free_n_clean(d, 1);
	exit (ec);
}

void	execve_errormsg2(t_data *d, t_com *current)
{
	if (access(current->file, X_OK) != 0)
	{
		ft_putstr_fd("minishell: Permission denied: ", 2);
		if (current->args && current->args[0])
			ft_putstr_fd(current->args[0], 2);
		ft_putstr_fd("\n", 2);
		close_clean_exit(d, 126);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		if (current->args && current->args[0])
			ft_putstr_fd(current->args[0], 2);
		ft_putstr_fd("\n", 2);
		close_clean_exit(d, 127);
	}
}

void	execve_errormsg1(t_data *d, t_com *current)
{
	if (current->file && (current->file[0] == '/'
			|| (current->file[0] == '.'
				& current->file[1] == '/') || (current->file[0] == '.'
				&& current->file[1] == '.' && current->file[2] == '/'))
		&& access(current->file, F_OK) != 0)
	{
		ft_putstr_fd("minishell: No such file or directory: ", 2);
		if (current->file)
			ft_putstr_fd(current->file, 2);
		ft_putstr_fd("\n", 2);
		close_clean_exit(d, 127);
	}
	else if (access(current->file, F_OK) != 0)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		if (current->args && current->args[0])
			ft_putstr_fd(current->args[0], 2);
		ft_putstr_fd("\n", 2);
		close_clean_exit(d, 127);
	}
	execve_errormsg2(d, current);
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
			ft_putstr_fd("\n", 2);
		}
		current = current->next;
	}
}
