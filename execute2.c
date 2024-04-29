#include "minishell.h"



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
	if ( i != 0)
	{
		if (d->old_fd[IN] < 0)
			dup2(d->p[i-1][0], STDIN_FILENO);
		else
			dup2(d->p[i-1][0], d->old_fd[IN]);
		close_pipes(d->p[i-1]);
	}
}

//child handler
void	playground(t_data *d, t_com *current ,int pc, int i)
{

	if (current->rdr)
		rdr_handler(d, current);
	if (pc != 0)
		pipe_handler(d, pc, i);

	if (execve(current->file, current->args, NULL) == -1)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(current->args[0], 2);
		ft_putstr_fd("\n", 2);
		free_n_clean(d, 1);
		exit(-1);
	}
}

void	process_handler(t_data *d, t_com *current, int pc, int i)
{
	char	*file;

	file = ft_strjoin(BIN, current->file);
	if (file == NULL)
		return ;
	free (current->file);
	current->file = file;
	if (pc != 0 && i != pc)
		pipe(d->p[i]);
	current->pid = fork();
	if (current->pid < 0)
		return ; // fork fail
	else if(current->pid == 0)
	{
		playground(d, current, pc, i);
	}
	else
	{
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
		close_rdr(d);
		i++;
		current = current->next;
	}
	current = d->com;
	while (current)
	{
		waitpid(current->pid, &(current->status), 0); 
		current = current->next;
	}

}


void	executor2(t_data *d)
{
	int	count;

	if (setup_fds(d) != 0)
		return ; //alloc error
	count = d_lstsize(d->com);
	if (count > 0)
	{
		if (count > 1 && setup_pipes(d, count - 1) != 0)
			return ; // alloc error
		execute_loop(d, count - 1);
	}
}



