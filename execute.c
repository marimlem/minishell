#include "minishell.h"

	// char *file = "/usr/bin/ls";
    // char *const args[] = {"/usr/bin/ls", "-a", "-l", NULL};
    // char *const env[] = {"ENV=World", NULL};
void	executor(t_cmd *cmd)
{
	cmd_execute(cmd);
	if (ft_strncmp(cmd->input, "exit", 4) == 0) //only for testing
	{

		free(cmd->input);
		cmd->input = NULL;
		exit(0); //leak of one
	}
	if (cmd->input)
	{
		free(cmd->input);
		cmd->input = NULL;
	}
}

int	cmd_lstsize(t_tok *lst)
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
	size = cmd_lstsize(p);
	// printf("size: %d\n", size);
	mat = (char**) malloc(sizeof(char *) * (size + 1));
	if (mat == NULL)
		return (NULL); //set error
	mat[size] = NULL;
	mat[i] = ft_strdup(file);
	if (mat[i++] == NULL)
		return (NULL); // set error
	p = p->next;
	while (p != NULL)
	{
		mat[i] = ft_strdup(p->tok);
		if (mat[i++] == NULL)
			return (NULL); // set error
		p = p->next;
	}
	return (mat);
}

void	cmd_execute(t_cmd *cmd)
{
	t_tok	*p;
	char	*file;
	char	**args;
			// int	i = 0;

	p = cmd->start->next;
	if (p == NULL)
		return ;
	file = ft_strjoin(BIN, p->tok);
	if (file == NULL)
		return ; // set error

	args = create_arg_mat(p, file);
	
			// testing purposes: matrix display
			// while (args[i])
			// {
			// 	printf("mat: %s\n", args[i++]);
			// }
	execve(file, args, NULL);
}
