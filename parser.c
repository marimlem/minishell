#include "minishell.h"

void	p_error(t_data *d)
{
	t_tok	*current;
	int		t;

	current = d->node;
	t=1;
	d->i = 0;
	while (current && current->tok)
	{
		if ((current->tok[0] == '>' || current->tok[0] == '<' || current->tok[0] == '|'))
		{
			if (ft_strlen(current->tok) > 2)
			{
				d->error = ERR_PAR_SYN;
				return ;
			}
			else if ((current->tok[1] && current->tok[0] == '|') || (current->tok[1] && current->tok[0] != current->tok[1]))
			{
				d->error = ERR_PAR_SYN;
				return ;
			}
			else if (ft_strlen(current->tok) == 1 || (current->tok[1] && current->tok[0] == current->tok[1]))
			{
				t = 1;
				current->typ = OP;
				current = current->next;
				continue ;
			}
		}
		else
			current->typ = t;
		t++;
		current = current->next;
	}
}

void	parser(t_data *d)
{
	p_error(d);
	// exp_n_rmquote();

	lst_print(d->node);


	(void) d;
	return ;
}