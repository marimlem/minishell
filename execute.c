#include "minishell.h"

	// char *file = "/usr/bin/ls";
    // char *const args[] = {"/usr/bin/ls", "-a", "-l", NULL};
    // char *const env[] = {"ENV=World", NULL};
void	heredoc_start(t_data *d)
{
	char *heredoc_input;
	// int	tmp_fd;
	(void) d;

	if (d->old_fd[IN] != 0)
		close(d->fd[IN]);
	else
		d->old_fd[IN] = dup(STDIN_FILENO);

	d->fd[IN] = open(".minishell_heredoc_tmp_file", O_WRONLY | O_CREAT | O_TRUNC , 0644);
	if (d->fd[IN] < 0)
		return ;
	// dup2(d->fd[IN], STDIN_FILENO);

	// heredoc_input = readline("heredoc> ");
	// ft_putstr_fd(heredoc_input, d->fd[IN]);
	(void) heredoc_input;

	while (1)
	{
		// rl_on_new_line();
		// printf("\nheredoc> ");
		heredoc_input = readline("heredoc> ");
		if (strcmp(heredoc_input, d->com->rdr[1]) == 0)
			break;
		ft_putstr_fd(heredoc_input, d->fd[IN]);
		ft_putchar_fd('\n', d->fd[IN]);
		// (void) heredoc_input;
		// printf("%s\n", heredoc_input);
	}
	close (d->fd[IN]);
	d->fd[IN] = open(".minishell_heredoc_tmp_file", O_RDONLY | O_CREAT , 0644);
	if (d->fd[IN] < 0)
		return ;
	

	dup2(d->fd[IN], STDIN_FILENO);

	// dup2(STDIN_FILENO, 2);
	// dup2(STDOUT_FILENO, 1);

}

int	rdr_handler(t_data *d)
{
	int	i;
	// int	j;


	// j = 0;
	i=0;
	d->old_fd = (int*) ft_calloc(sizeof(int), 3);
	if (d->old_fd ==NULL)
		return (1);
	d->fd = (int*) ft_calloc(sizeof(int), 3);
	if (d->fd ==NULL)
		return (1);
	while (d->com->rdr[i])
	{
		if (d->com->rdr[i][0] == '>')// && d->com->rdr[i][1] == 0) // redirect output to file
		{
			if (d->old_fd[OUT] == 0)
				d->old_fd[OUT] = dup(STDOUT_FILENO);
			else
				close(d->fd[OUT]);
			if (d->com->rdr[i][1] == 0)
				d->fd[OUT] = open(d->com->rdr[i + 1], O_WRONLY |O_CREAT |O_TRUNC, 0644); 
			else
				d->fd[OUT] = open(d->com->rdr[i + 1], O_WRONLY |O_CREAT|O_APPEND, 0644); 
			if (d->fd[OUT] < 0)
			{
				printf("rdr: error opening file\n");
				dup2(d->old_fd[OUT], 1);
				return (1);
			}
			dup2(d->fd[OUT], STDOUT_FILENO);
		}
		else if (d->com->rdr[i][0] == '<' && d->com->rdr[i][1] == 0)
		{
			//printf("oldfd[IN]: %d\nfd[IN]: %d\n\n", d->old_fd[IN], d->fd[IN]);
			if (d->old_fd[IN] != 0)
				close(d->fd[IN]);
			else
				d->old_fd[IN] = dup(STDIN_FILENO);
			d->fd[IN] = open(d->com->rdr[i+1], O_RDONLY);
			//printf("oldfd[IN]: %d\nfd[IN]: %d", d->old_fd[IN], d->fd[IN]);
			if (d->fd[IN] < 0)
				{
					printf("rdr: error opening file\n");
					dup2(d->old_fd[IN], 0);
					return (1);
				}
			dup2(d->fd[IN], STDIN_FILENO);
		}
		else if (d->com->rdr[i][0] == '<' && d->com->rdr[i][1] == '<') //heredoc
		{
			// if (d->old_fd[IN] != 0)
			// 	close(d->fd[IN]);
			// else
			// 	d->old_fd[IN] = dup(STDIN_FILENO);
			// dup2(d->fd[IN], STDIN_FILENO);
			heredoc_start(d);
		}

		i = i + 2;
	}
	return (0);
}



void	executor(t_data *d)
{
	t_com *current;

	current = d->com;
	if (current->rdr)
	{
		if (rdr_handler(d) != 0)
		{
			// d->error = 555;
			return ;
		}
		d_execute(d);
		

		if (d->old_fd[OUT])
		{
			dup2(d->old_fd[OUT], 1);
			close(d->fd[OUT]);
		}
		if (d->old_fd[IN])
		{
			dup2(d->old_fd[IN], 0);
			close(d->fd[IN]);
			d->fd[IN] = open(".minishell_heredoc_tmp_file", O_TRUNC , 0644);
			if (d->fd[IN] > 0)
				close(d->fd[IN]);
			

		}

	}
	else
	{
		if (current->next)
		{
			printf("p[0]: %d\np[1]: %d\n", d->p[0], d->p[1]);
			if (pipe(d->p) < 0)
				return ;
			printf("p[0]: %d\np[1]: %d\n", d->p[0], d->p[1]);

			// if (d->old_fd[OUT] == 0)
				// d->old_fd[OUT] = dup(STDOUT_FILENO);
			// else
			// 	close(d->fd[OUT]);

 			// dup2(d->p[1], STDOUT_FILENO);
			// close(d->p[0]);
			// dup2(STDOUT_FILENO, d->p[1]);
		}
		d_execute(d);
		if (current->next)
		{
			current = current->next;
			d_execute(d);
		}
		close (d->p[0]); //close both ends, the fds in parent process are untouched
		close (d->p[1]);
	}
	

}

int	d_lstsize(t_tok *lst)
{
	int		i;
	t_tok	*current;

	current = lst;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}


void	d_execute(t_data *d)
{
	char	*file;
	__pid_t	pid;
	__pid_t	status;

	file = ft_strjoin(BIN, d->com->file);
	if (file == NULL)
		return ; // set error
	free (d->com->file);
	d->com->file = file;

	pid = fork();
	if (pid == -1)
	{
		return ; // set error
	}
	else if (pid == 0)
	{
		dup2(d->p[0], STDIN_FILENO);
		close(d->p[1]);

		// dup2(STDIN_FILENO, d->p[0]);
		// dup2(1, d->p[1]);
		if (execve(d->com->file, d->com->args, NULL) == -1)
		{
			printf("minishell: command not found: %s\n",&d->com->file[9]);
			free_n_clean(d, 1);
			exit(-1);
		}
	}
	else
	{
		// dup2(d->p[1], STDOUT_FILENO);
		// close(d->p[0]);
		waitpid(pid, &status, 0);
	}
}
