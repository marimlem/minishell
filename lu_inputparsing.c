#include "minishell.h"

void	inputparsing(t_data *d, t_envlist **envlist)
{
	signal_setup(d, MODE_IN);
	d->input = readline("minishell:$ ");
	if (!d->input)
	{
		ft_putstr_fd("exit\n", 1);
		free_n_clean(d, 1);
		exit(0);
	}
	signal_setup(d, MODE_DF);


/* 	if (isatty(fileno(stdin)))
	{

		d->input = readline("minishell:$ ");
		if (!d->input)
		{
			ft_putstr_fd("exit\n", 1);
			free_n_clean(d, 1);
			exit(0);
		}
	}
	else
	{
		char *line;
		line = get_next_line(fileno(stdin));
		d->input = ft_strtrim(line, "\n");
		free(line);
	} */
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
	(void) envlist;
	// if (d->com && d->com->args && ft_strcmp(d->com->args[0], "env") == 0)
	// 	ft_print_list(*envlist);
		// printf("even!");

	//parser

}