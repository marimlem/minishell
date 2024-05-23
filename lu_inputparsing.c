#include "minishell.h"

void	inputparsing(t_data *d)
{
	if (isatty(fileno(stdin)))
		d->input = readline("minishell:$ ");
	else
	{
		char *line;
		line = get_next_line(fileno(stdin));
		d->input = ft_strtrim(line, "\n");
		free(line);
	}
	add_history(d->input);
	if (!d || !d->input)
		return ;
	if (even_quotes(d) == ODD)
		return ;
	lexer(d);
	parser(d);
	//parser

}