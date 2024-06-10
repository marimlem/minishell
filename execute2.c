/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:22:02 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/10 19:22:03 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//child handler
void	playground(t_data *d, t_com *current ,int pc, int i)
{
	int	ec;

	ec = 0;
	if (current->rdr && rdr_handler(d, current) != 0)
	{
		free_n_clean(d, 1);
		exit (1); // i think this might generate errors (originally -1)
	}
	if (pc != 0)
		pipe_handler(d, pc, i);

	if (current->builtin == 1)
	{
		execute_builtin(d, current, 0);
		if (d->exit_code != 0)
			ec = d->exit_code;
		free_n_clean(d, 1);
		exit (ec);
	}
	if (!current->args || !current->args[0])
	{
		free_n_clean(d, 1);
		exit(0);
	}
   	else if (execve(current->file, current->args, d->envp) == -1)
	{
		if (current->file && (current->file[0] == '/' || (current->file[0] == '.' && current->file[1] == '/') || (current->file[0] == '.' && current->file[1] == '.' && current->file[2] == '/')) && access(current->file , F_OK) != 0)
		{
			ft_putstr_fd("minishell: No such file or directory: ", 2);
			if (current->file)
				ft_putstr_fd(current->file, 2);
			ft_putstr_fd("\n", 2);
			free_n_clean(d, 1);
			exit(127);
		}
		else if (access(current->file , F_OK) != 0)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			if (current->args && current->args[0])
				ft_putstr_fd(current->args[0], 2);
			ft_putstr_fd("\n", 2);
			free_n_clean(d, 1);
			exit(127);
		}
		else if (access(current->file , X_OK) != 0)
		{
			ft_putstr_fd("minishell: Permission denied: ", 2);
			if (current->args && current->args[0])
				ft_putstr_fd(current->args[0], 2);
			ft_putstr_fd("\n", 2);
			free_n_clean(d, 1);
			exit(126);
		}
		else
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			if (current->args && current->args[0])
				ft_putstr_fd(current->args[0], 2);
			ft_putstr_fd("\n", 2);
			free_n_clean(d, 1);
			exit(127);
		}
	}
}



void	process_handler(t_data *d, t_com *current, int pc, int i)
{
	int	ec;


	ec = 0;

	d->heredoc_fd = 0;
	early_heredoc(d, current);
	if (g_signal_int == 130)
	{
		return ;
	}
  
	//simple command without pipes
	if (pc == 0 && current->builtin == 1)
	{
		if (rdr_handler(d, current) != 0)
			return ;
		execute_builtin(d, current, ec);
		return ;
	}


	if (pc != 0 && i != pc)
		pipe(d->p[i]);
	
	current->pid = fork();
	if (current->pid < 0)
		return ; // fork fail
	else if(current->pid == 0)
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
	int	i;

	i = 0;
	current = d->com;
	while (current)
	{
		process_handler(d, current, pc, i);
		if (g_signal_int == 130)
			return ; // won't this create zombie children? if cat cat ls, the forks won't be collected with waitpid?
		close_rdr(d);
		i++;
		current = current->next;
		usleep(5);
	}
	current = d->com;
	if (pc == 0 && current->builtin == 1)
		return ;
	while (current)
	{
		waitpid(current->pid, &(current->status), 0); 
		// ft_putnbr_fd(current->status, 2);
		// ft_putstr_fd("...", 2);
		d->exit_code = current->status %255;
		// ft_putnbr_fd(d->exit_code, 2);
		current = current->next;
	}
	if (d->exit_code == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	signal_setup(d, MODE_DF);



}

void	executor2(t_data *d)
{
	int	count;

	if (setup_fds(d) != 0 || setup_path(d) != 0 || setup_cmdpath(d) != 0)
		return ; //alloc error
	count = d_lstsize(d->com);
	if (count > 0)
	{
		if (count > 1 && setup_pipes(d, count - 1) != 0)
			return ; // alloc error
		execute_loop(d, count - 1);
	}
}



