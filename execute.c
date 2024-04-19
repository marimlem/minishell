#include "minishell.h"

	// char *file = "/usr/bin/ls";
    // char *const args[] = {"/usr/bin/ls", "-a", "-l", NULL};
    // char *const env[] = {"ENV=World", NULL};
void	heredoc_start(t_data *d)
{
	(void) d;
	printf("heredoc> ");


}

void	rdr_handler(t_data *d)
{
	int	i;
	// int	j;


	// j = 0;
	i=0;
	d->old_fd = (int*) ft_calloc(sizeof(int), 3);
	if (d->old_fd ==NULL)
		return;
	d->fd = (int*) ft_calloc(sizeof(int), 3);
	if (d->fd ==NULL)
		return;
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
				return ;
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
					return ;
				}
			dup2(d->fd[IN], STDIN_FILENO);
		}
		else if (d->com->rdr[i][0] == '<' && d->com->rdr[i][1] == '<') //heredoc
		{
			if (d->old_fd[IN] != 0)
				close(d->fd[IN]);
			else
				d->old_fd[IN] = dup(STDIN_FILENO);
			dup2(d->fd[IN], STDIN_FILENO);
			heredoc_start(d);
		}

		i = i + 2;
	}
}


void	executor(t_data *d)
{
	// int	i = 0;

	if (d->com->rdr)
	{
		rdr_handler(d);

		d_execute(d);
		
		//resetting rdr 
		// printf("old out: %d\n", d->old_fd);

		if (d->old_fd[OUT])
		{
			dup2(d->old_fd[OUT], 1);
			close(d->fd[OUT]);
		}
		if (d->old_fd[IN])
		{
			dup2(d->old_fd[IN], 0);
			close(d->fd[IN]);

		}


		// while (d->old_fd[OUT])
		// {

		// 	dup2(d->old_fdold_fd[OUT], 1);
		// 	close(d->fd[OUT]);
		// 	i--;
		// }
	}
	else
		d_execute(d);
	

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

		if (execve(d->com->file, d->com->args, NULL) == -1)
		{
			printf("minishell: command not found: %s\n",&d->com->file[9]);
			free_n_clean(d, 1);
			exit(-1);
		}
	}
	else
		waitpid(pid, &status, 0);
}
