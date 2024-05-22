#include "minishell.h"

void	inputparsing(t_data *d)
{
	d->input = readline("minishell:$ ");
	if (!d || !d->input)
		return ;
	if (even_quotes(d) == ODD)
		return ;
	/* if (ft_strncmp(d->input, "exit", 4) == 0)
	{
		d->error = -1;
		return ;
	} */

	lexer(d);
	parser(d);
}

int	is_builtin(t_data *d)
{
	if (ft_strcmp(d->com->args[0], "echo") == 0)
		return 1;
	else if (ft_strcmp(d->com->args[0], "cd") == 0)
		return 2;
	else if (ft_strcmp(d->com->args[0], "pwd") == 0)
		return 3;
	else if (ft_strcmp(d->com->args[0], "export") == 0)
		return 4;
	else if (ft_strcmp(d->com->args[0], "unset") == 0)
		return 5;
	else if (ft_strcmp(d->com->args[0], "env") == 0)
		return 6;
	else if (ft_strcmp(d->com->args[0], "exit") == 0)
		return 7;
	else
		return 8;
	return 0;
}