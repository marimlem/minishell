#include "minishell.h"

int	is_all_white(char *input)
{
	int	i;

	i = 0;
	while(input && input[i])
	{
		if (input[i] == ' ' || input[i] == '\t' || input[i] == '\r' || input[i] == '\n' || input[i] == '\v' || input[i] == '\f')
			i++;
		else
			return (1);
	}
	return (0);
}

void	exit_n_clean(t_data *d, char *str, int ec)
{
	ft_putstr_fd(str, 2);
	free_n_clean(d, 1);
	exit (ec);
}

void	inputparsing(t_data *d)
{
	signal_setup(d, MODE_IN);
	d->input = readline("minishell:$ ");
	if (!d->input)
		exit_n_clean(d, "exit\n", d->exit_code);
	if (g_signal_int == 130)
	{
		d->exit_code = 130;
		g_signal_int = 0;
	}
	signal_setup(d, MODE_DF);
	if (ft_strcmp(d->input, "") == 0 || is_all_white(d->input) == 0)
		return ;
	add_history(d->input);
	if (!d || !d->input)
		return ;
	if (even_quotes(d) == ODD)
		return ;
	lexer(d);
	parser(d);
}
