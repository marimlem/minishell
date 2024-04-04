#include "minishell.h"

	// char *file = "/usr/bin/ls";
    // char *const args[] = {"/usr/bin/ls", "-a", "-l", NULL};
    // char *const env[] = {"ENV=World", NULL};
void	executor(t_data *d)
{
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
		execve(d->com->file, d->com->args, NULL);
	else
		waitpid(pid, &status, 0);
}
