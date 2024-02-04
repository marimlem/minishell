#include "minishell.h"


// finds and marks operator tokens
void	p_op_type(t_data *d)
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


// finds and marks proper variable assignment tokens
void	p_var(t_data *d)
{
	t_tok *current;

	current = d->node;
	d->i = 0;
	while (current && current->tok)
	{
		d->i = 0;
		if (current->typ == OP)
		{
			current = current->next;
			continue ;
		}
		while (current->tok[d->i])
		{
			if (current->tok[d->i] == SGLQUOTE || current->tok[d->i] == DBLQUOTE)
				break ;
			if (current->tok[d->i] == '=')
			{
				current->typ = VAR;
				break ;
			}
			d->i++;
		}
		current = current->next;
	}
}

void	parser(t_data *d)
{
	p_op_type(d);
	// lst_print(d->node);
	p_var(d);

	
	// exp_n_rmquote();

	lst_print(d->node);


	(void) d;
	return ;
}