#include "minishell.h"

void	inputparsing(t_data *d)
{
	d->input = readline("minishell:$ ");
	if (!d || !d->input)
		return ;
	if (even_quotes(d) == ODD)
		return ;

	lexer(d);
	parser(d);
		// printf("even!");

	//parser

}