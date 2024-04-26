#include "minishell.h"

// no pipes, just one command
void	execute_one(t_data *d)
{
	(void) d;
	return ;
}

int	rdr_out(t_data *d, t_com *current, int j)
{
	if (d->old_fd == 0)
		d->old_fd[OUT] = dup(STDOUT_FILENO);
	else
		close(d->fd[OUT]);
	if (current->rdr[j][1] == 0)
		d->fd[OUT] = open(current->rdr[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		d->fd[OUT] = open(current->rdr[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(d->fd[OUT] < 0)
	{
		printf("rdr > : error opening file\n");
		dup2(d->old_fd[OUT], 1);
		return (1);
	}
	return (0);
}

int	rdr_in(t_data *d, t_com *current, int j)
{
	if (d->old_fd[IN] != 0)
		close(d->fd[IN]);
	else
		d->old_fd[IN] = dup(STDIN_FILENO);
	if (current->rdr[j][1] == '<')
		heredoc_start(d, current);
	else
	{
		d->fd[IN] = open(current->rdr[j + 1], O_RDONLY);
		if (d->fd[IN] < 0)
		{
			printf("rdr <: error opening file\n");
			dup2(d->old_fd[IN], 0);
			return (1);
		}
		dup2(d->fd[IN], STDIN_FILENO);
	}
	return (0);
}

void	heredoc_start(t_data *d, t_com *current)
{
	char *heredoc_input;

	heredoc_input = NULL;
	d->fd[IN] = open(".minishell_heredoc_tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->fd[IN] < 0)
		return ;
	while (1)
	{
		heredoc_input = readline("heredoc> ");
		if (strcmp(heredoc_input, current->rdr[1]) == 0)
			break ;
		ft_putstr_fd(heredoc_input, d->fd[IN]);
		ft_putchar_fd('\n', d->fd[IN]);
	}
	close (d->fd[IN]);
	d->fd[IN] = open(".minishell_heredoc_tmp_file", O_RDONLY | O_CREAT, 0644);
	if (d->fd[IN] < 0)
		return ;
	dup2(d->fd[IN], STDIN_FILENO);
}


int	rdr_handler(t_data *d, t_com *current)
{
	int	j;

	j = 0;
	while (current->rdr[j])
	{
		if (current->rdr[j][0] == '>')
		{
			rdr_out(d, current, j);
			//what happens when rdr fails? should abort rdr or continue with next rdr
		}
		else if (current->rdr[j][0] == '<')
		{
			rdr_in(d, current, j);
		}
		j = j + 2;

	}
	return (0);

}

void	pipe_handler(t_data *d, int pc, int i)
{
	if (i != pc)
	{
		dup2(d->p[i][1], STDOUT_FILENO);
		close_pipes(d->p[i]);
	}
	if ( i != 0)
	{
		dup2(d->p[i-1][0], STDIN_FILENO);
		close_pipes(d->p[i-1]);
	}
}

//child handler
void	playground(t_data *d, t_com *current ,int pc, int i)
{

	if (current->rdr)
		rdr_handler(d, current);
	pipe_handler(d, pc, i);

	if (execve(current->file, current->args, NULL) == -1)
	{
		printf("minishell: command not found: %s\n",current->args[0]); //file[9]);
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
	if (i != pc)
		pipe(d->p[i]);
	d->pid = fork();
	if (d->pid < 0)
		return ; // fork fail
	else if(d->pid == 0)
	{
		//rdr //piping //exec
		playground(d, current, pc, i);
	}
	else
	{
		if (i != 0)
			close_pipes(d->p[i - 1]);
		waitpid(d->pid, &(d->status), 0);
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
		i++;
		current = current->next;
		d->status = 0;
		d->pid = 0;
	}
}


void	executor2(t_data *d)
{
	int	count;

	if (setup_fds(d) != 0)
		return ; //alloc error
	count = d_lstsize(d->com);
	printf("fd: %d ... count: %d\n", d->fd[0], count);
	if (count == 1)
		execute_one(d);
	else if (count > 1)
	{
		if (setup_pipes(d, count - 1) != 0)
			return ; // alloc error
		execute_loop(d, count - 1);
	}
}



