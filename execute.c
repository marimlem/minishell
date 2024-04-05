#include "minishell.h"

	// char *file = "/usr/bin/ls";
    // char *const args[] = {"/usr/bin/ls", "-a", "-l", NULL};
    // char *const env[] = {"ENV=World", NULL};


void	rdr_handler(t_data *d)
{
	int	i;

	i=0;
	d->fd=0;
	if (d->com->rdr[i][0] == '>') // redirect output to file
	{
		d->old_out = dup(STDOUT_FILENO);
		// close(STDOUT_FILENO);
		d->fd = open(d->com->rdr[i+1], O_WRONLY |O_CREAT, 0644);
		if (d->fd < 0)
		{
			printf("rdr: error opening file\n");
			return ;
		}
		dup2(d->fd, STDOUT_FILENO);
	}
}


void	executor(t_data *d)
{
	if (d->com->rdr)
	{
		rdr_handler(d);

		d_execute(d);
		
		//resetting rdr 
		// printf("old out: %d\n", d->old_out);
		dup2(d->old_out, 1);
		close(d->fd);
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
