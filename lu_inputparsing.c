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

void	inputparsing(t_data *d)
{
	signal_setup(d, MODE_IN);
	// ft_putnbr_fd(d->exit_code, 2);
	d->input = readline("minishell:$ ");
	if (!d->input)
	{
		ft_putstr_fd("exit\n", 1);
		free_n_clean(d, 1);
		exit(d->exit_code);
	}
	// g_signal_int = 130;
	if (g_signal_int == 130)
	{
		// ft_putnbr_fd(g_signal_int, 2);
		// ft_putstr_fd("... :)\n", 2);

		d->exit_code = 130;
		g_signal_int = 0;
		// ft_putnbr_fd(d->exit_code, 2);

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