#include "minishell.h"

	// char *file = "/usr/bin/ls";
    // char *const args[] = {"/usr/bin/ls", "-a", "-l", NULL};
    // char *const env[] = {"ENV=World", NULL};
void	executor(t_data *d)
{
	d_execute(d);
	if (ft_strncmp(d->input, "exit", 4) == 0) //only for testing
	{

		free(d->input);
		d->input = NULL;
		exit(0); //leak of one
	}
	if (d->input)
	{
		free(d->input);
		d->input = NULL;
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

char	**create_arg_mat(t_tok *p, char *file)
{
	int	size;
	char	**mat;
	int	i;

	i = 0;
	size = d_lstsize(p);
	// printf("size: %d\n", size);
	mat = (char**) malloc(sizeof(char *) * (size + 1));
	if (mat == NULL)
		return (NULL); //set error
	mat[size] = NULL;
	mat[i] = ft_strdup(file);
	if (mat[i++] == NULL)
		return (NULL); // set error
	// p = p->next;
	while (p->tok != NULL && i != size)
	{
		mat[i] = ft_strdup(p->tok);
		if (mat[i++] == NULL)
			return (NULL); // set error
		p = p->next;
		if (p == NULL)
			break ;
	}
	return (mat);
}

void	d_execute(t_data *d)
{
	t_tok	*p;
	char	*file;
	char	**args;
	__pid_t	pid;
	__pid_t	status;
			// int	i = 0;

	p = d->node;
	file = ft_strjoin(BIN, p->tok);
	if (file == NULL)
		return ; // set error

	args = create_arg_mat(p, file);
	
			// testing purposes: matrix display
			// while (args[i])
			// {
			// 	printf("mat: %s\n", args[i++]);
			// }
	pid = fork();
	if (pid == -1)
	{
		return ; // set error
	}
	else if (pid == 0)
		execve(file, args, NULL);
	else
		waitpid(pid, &status, 0);
}
