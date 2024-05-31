#include "minishell.h"

void	inputparsing(t_data *d)
{
	// d->input = readline("minishell:$ ");
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
	// if (ft_strncmp(d->input, "exit", 4) == 0)
	// {
	// 	d->error = -1;
	// 	return ;
	// }

	lexer(d);
	parser(d);
	// if (d->com && d->com->args && ft_strcmp(d->com->args[0], "env") == 0)
	// 	ft_print_list(*envlist);
		// printf("even!");

	//parser

}