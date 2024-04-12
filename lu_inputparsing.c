#include "minishell.h"

void	inputparsing(t_data *d, t_envlist **envlist)
{
	d->input = readline("minishell:$ ");
	if (!d || !d->input)
		return ;
	if (even_quotes(d) == ODD)
		return ;
	if (ft_strncmp(d->input, "exit", 4) == 0)
	{
		d->error = -1;
		return ;
	}

	lexer(d);
	parser(d);
	if (ft_strcmp(d->com->args[0], "env") == 0)
		ft_print_list(*envlist);
		// printf("even!");

	//parser

}