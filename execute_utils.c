#include "minishell.h"

int	setup_fds(t_data *d)
{
	d->old_fd = (int*) ft_calloc(sizeof(int), 3);
	if (d->old_fd ==NULL)
		return (1);
	d->fd = (int*) ft_calloc(sizeof(int), 3);
	if (d->fd ==NULL)
		return (1);
	d->fd[IN] = dup(STDIN_FILENO);
	d->fd[OUT] = dup(STDOUT_FILENO);
	// d->old_fd[IN] = dup(STDIN_FILENO); //need this in rdr_handler to see if it's the first 
	// d->old_fd[OUT] = dup(STDOUT_FILENO);
	return (0);
}

int	setup_pipes(t_data *d, int pipecount)
{
	int	i;

	i = 0;
	d->p = (int **) ft_calloc(sizeof(int*), pipecount);
	if (d->p == NULL)
		return (1); //alloc error
	while (i != pipecount)
	{
		d->p[i] = (int *) ft_calloc(sizeof(int), 2);
		if (d->p[i] ==NULL)
			return (1);
		i++;
	}
	return (0);
}

int	d_lstsize(t_com *lst)
{
	int		i;
	t_com	*current;

	current = lst;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	close_pipes(int *tube)
{
	close (tube[0]);
	close (tube[1]);
}
