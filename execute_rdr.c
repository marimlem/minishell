#include "minishell.h"

void	close_rdr(t_data *d)
{
		if (d->old_fd[OUT] >= 0)
		{
			dup2(d->old_fd[OUT], 1);
			close(d->fd[OUT]);
		}
		if (d->old_fd[IN] >= 0)
		{
			dup2(d->old_fd[IN], 0);
			close(d->fd[IN]);
			d->fd[IN] = open(".minishell_heredoc_tmp_file", O_WRONLY| O_CREAT | O_TRUNC , 0644);
			if (d->fd[IN] > 0)
				close(d->fd[IN]);
		}
		else
		{	
			d->fd[IN] = open(".minishell_heredoc_tmp_file", O_TRUNC , 0644);
			if (d->fd[IN] > 0)
				close(d->fd[IN]);
		}
}

int	rdr_out(t_data *d, t_com *current, int j)
{
	if (d->old_fd[OUT] < 0) // first round
		d->old_fd[OUT] = dup(STDOUT_FILENO);
	else if (d->fd[OUT] > 0)
		close(d->fd[OUT]);
	if (current->rdr[j][1] == 0)
		d->fd[OUT] = open(current->rdr[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		d->fd[OUT] = open(current->rdr[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(d->fd[OUT] < 0)
	{
		// printf("rdr > : error opening file\n");
		// ft_putstr_fd("rdr > : error opening file\n", 2);
		dup2(d->old_fd[OUT], 1);
		return (j + 1);
	}
	dup2(d->fd[OUT], STDOUT_FILENO);
	return (0);
}

int	rdr_in(t_data *d, t_com *current, int j)
{
	if (d->old_fd[IN] < 0)
		d->old_fd[IN] = dup(STDIN_FILENO);
	else if (d->fd[IN] > 0)
		close(d->fd[IN]);
	if (current->rdr[j][1] == '<' && heredoc_start(d, current, j) != 0)
		return (j + 1);
	else
	{
		d->fd[IN] = open(current->rdr[j + 1], O_RDONLY);
		if (d->fd[IN] < 0)
		{
			// printf("rdr <: error opening file\n");
			// ft_putstr_fd("rdr < : error opening file\n", 2);
			dup2(d->old_fd[IN], 0);
			return (j + 1);
		}
		dup2(d->fd[IN], STDIN_FILENO);
	}
	return (0);
}

int	heredoc_start(t_data *d, t_com *current, int j)
{
	char *heredoc_input;

	heredoc_input = NULL;
	d->fd[IN] = open(".minishell_heredoc_tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->fd[IN] < 0)
		return (j + 1);
	while (1)
	{
		heredoc_input = readline("heredoc> ");
		if (strcmp(heredoc_input, current->rdr[j + 1]) == 0)
			break ;
		ft_putstr_fd(heredoc_input, d->fd[IN]);
		ft_putchar_fd('\n', d->fd[IN]);
	}
	if (d->fd[IN] != -1)
		close (d->fd[IN]);
	d->fd[IN] = open(".minishell_heredoc_tmp_file", O_RDONLY | O_CREAT, 0644);
	if (d->fd[IN] < 0)
		return (j + 1);
	dup2(d->fd[IN], STDIN_FILENO);
	return (0);
}


int	rdr_handler(t_data *d, t_com *current)
{
	int	j;
	int	error;

	j = 0;
	error = 0;
	while (current->rdr[j])
	{
		if (current->rdr[j][0] == '>')
		{
			// return (1);
			if (error == 0)
				error = rdr_out(d, current, j);
			else
				rdr_out(d, current, j);

			//what happens when rdr fails? should abort rdr or continue with next rdr
		}
		else if (current->rdr[j][0] == '<')
		{
			if (error == 0)
				error = rdr_in(d, current, j);
			else
				rdr_in(d, current, j);

			// return (1);
		}
		j = j + 2;
	}
	if (error != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(current->rdr[error], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}

	return (error);
}
