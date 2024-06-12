/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:22:02 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/12 20:13:15 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//child handler
void	playground(t_data *d, t_com *current, int pc, int i)
{
	int	ec;

	ec = 0;
	if (current->rdr && rdr_handler(d, current) != 0)
		close_clean_exit(d, 1);
	if (pc != 0)
		pipe_handler(d, pc, i);
	if (current->builtin == 1)
	{
		execute_builtin(d, current, 0);
		if (d->exit_code != 0)
			ec = d->exit_code;
		close_clean_exit(d, ec);
	}
	if (!current->args || !current->args[0])
		close_clean_exit(d, 0);
	else if (execve(current->file, current->args, d->envp) == -1)
	{
		execve_errormsg1(d, current);
	}
}

int	simple_command(t_data *d, t_com *current, int ec, int pc)
{
	if (pc == 0 && current->builtin == 1)
	{
		if (rdr_handler(d, current) != 0)
			return (0);
		execute_builtin(d, current, ec);
		return (0);
	}
	else
		return (1);
}

void	process_handler(t_data *d, t_com *current, int pc, int i)
{
	int	ec;

	ec = 0;
	d->heredoc_fd = 0;
	early_heredoc(d, current);
	if (g_signal_int == 130)
		return ;
	if (simple_command(d, current, ec, pc) == 0)
		return ;
	if (pc != 0 && i != pc)
		pipe(d->p[i]);
	current->pid = fork();
	if (current->pid < 0)
		return ;
	else if (current->pid == 0)
	{
		signal_setup(d, MODE_DF);
		playground(d, current, pc, i);
	}
	else
	{
		signal_setup(d, MODE_IG);
		if (pc != 0 && i != 0)
			close_pipes(d->p[i - 1]);
	}
}


// pc == pipecount
void	execute_loop(t_data *d, int pc)
{
	t_com	*current;
	int		i;

	i = 0;
	current = d->com;
	while (current)
	{
		process_handler(d, current, pc, i);
		if (g_signal_int == 130)
			return ;
		close_rdr(d);
		i++;
		current = current->next;
	}
	current = d->com;
	if (pc == 0 && current->builtin == 1)
		return ;
	get_exit_status(d, current);
	// print_coredumped(d->exit_code);
	signal_setup(d, MODE_DF);
}

void	executor2(t_data *d)
{
	int	count;

	if (setup_fds(d) != 0 || setup_path(d) != 0 || setup_cmdpath(d) != 0)
		return ;
	count = d_lstsize(d->com);
	if (count > 0)
	{
		if (count > 1 && setup_pipes(d, count - 1) != 0)
			return ;
		execute_loop(d, count - 1);
	}
}
