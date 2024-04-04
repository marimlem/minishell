#include "minishell.h"

void	inputparsing(t_data *d)
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
		// printf("even!");

	//parser

}