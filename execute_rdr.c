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
			if (d->fd[IN] >= 0)
				close(d->fd[IN]);
		}
		else
		{	
			d->fd[IN] = open(".minishell_heredoc_tmp_file", O_TRUNC , 0644);
			if (d->fd[IN] >= 0)
				close(d->fd[IN]);
		}
}

int	rdr_out(t_data *d, t_com *current, int j)
{
	if (d->old_fd[OUT] < 0) // first round
		d->old_fd[OUT] = dup(STDOUT_FILENO);
	else if (d->fd[OUT] >= 0)
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
	else if (d->fd[IN] >= 0)
	{
		close(d->fd[IN]);
		d->fd[IN] = -1;
	}
	if (current->rdr[j][1] == '<') //&& heredoc_start(d, current, j) != 0)
	{
		if (heredoc_start(d, current, j) != 0)
			return (j + 1);
		else
			return (0);
	}
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
	// char *heredoc_input;

	// heredoc_input = NULL;
	(void) current;
	(void) j;
	if (d->old_fd[IN] != -1)
		dup2(d->old_fd[IN], 0);
	// g_signal_int = 2;

	// if (d->heredoc_fd < 0)
	// 	return (j + 1);

	// d->fd[IN] = dup(d->heredoc_fd);
	// dup2(d->fd[IN], d->heredoc_fd);
	// d->fd[IN] = open(".minishell_heredoc_tmp_file", O_RDWR | O_CREAT , 0644);


	d->fd[IN] = open("/home/lknobloc/Documents/minishell/minishell_heredoc_tmp_file", O_RDONLY | O_CREAT, 0644);
	if (d->fd[IN] < 0)
		return (d->heredoc_fd + 1);
	dup2(d->fd[IN], STDIN_FILENO);
	return (0);
/* 	
	// dup2(d->fd[IN], STDIN_FILENO);
	
	while (g_signal_int == 2)
	{
		//gnl
		ft_putstr_fd("> ", 2);
		heredoc_input = get_next_line(STDIN_FILENO);
		if (g_signal_int != 2)
			break ;
		if (!heredoc_input)
		{
			free_n_clean(d, 1);
			exit (-2);
			// break ; // control D should exit everything
		}
		if (strncmp(heredoc_input, current->rdr[j + 1], ft_strlen(current->rdr[j + 1])) == 0 && heredoc_input[ft_strlen(current->rdr[j + 1])] == '\n')
			break ;
		ft_putstr_fd(heredoc_input, d->fd[IN]);

		//readline
		// ft_putstr_fd("> ", 2);
		// heredoc_input = readline("");


		// if (strcmp(heredoc_input, current->rdr[j + 1]) == 0)
		// 	break ;
		// if (current->rdr[j][2] != SGLQUOTE)
		// {
		// 	heredoc_input = heredoc_expanding(d, heredoc_input);
		// 	if (heredoc_input == NULL)
		// 		return (j + 1);
		// }
		// ft_putstr_fd(heredoc_input, d->fd[IN]);
		// ft_putchar_fd('\n', d->fd[IN]);
	}
	g_signal_int = 1;
	if (d->fd[IN] >= 0)
		close (d->fd[IN]);
	d->fd[IN] = open(".minishell_heredoc_tmp_file", O_RDONLY | O_CREAT, 0644);
	if (d->fd[IN] < 0)
		return (j + 1);
	dup2(d->fd[IN], STDIN_FILENO);
	return (0); */
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
		if (current->rdr[error-1][0] == '<' && current->rdr[error-1][1] == '<')
			ft_putstr_fd("heredoc error\n", 2);
		else
		{
			ft_putstr_fd(current->rdr[error], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
	}

	return (error);
}
