#include "minishell.h"

void	inputparsing(t_data *d)
{
	d->input = readline("minishell:$ ");
	if (!d || !d->input)
		return ;
	if (even_quotes(d) == EVEN)
	{
		lexer(d);
		// printf("even!");
	}

	//parser

}