#include "minishell.h"

void	inputparsing(t_data *d)
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
	add_history(d->input);
	if (!d || !d->input)
		return ;
	if (even_quotes(d) == ODD)
		return ;
	lexer(d);
	parser(d);
}