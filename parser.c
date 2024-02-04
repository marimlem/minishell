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

// checks if operators are in syntactically good order (not first, not last, not two in a row)
void	p_syn_check(t_data *d)
{
	t_tok *current;
	int	t;
	int	last;

	t = 0;
	last = 0;
	current = d->node;
	while (current && current->tok)
	{
		if (t == 0 && current->typ == OP)
		{
			d->error = ERR_PAR_SYN;
			return ;
		}
		else if (current->typ == OP && last == OP)
		{
			d->error = ERR_PAR_SYN;
			return ;
		}
		last = current->typ;
		t++;
		current = current->next;
	}
	if (last == OP)
		d->error = ERR_PAR_SYN;
}

// quote handler and expander
void	p_quote_exp(t_data *d)
{
	t_tok *current;
	int	q;

	q = 0;
	d->i = 0;
	current = d->node;
	while (current && current->tok)
	{
		while (current->tok[d->i])
		{
			if (q == 0 && (current->tok[d->i] == SGLQUOTE || current->tok[d->i] == DBLQUOTE))
				q = current->tok[d->i];
			if (q != 0 && current->tok[d->i] == q)
				q = 0;
			if (q != SGLQUOTE && current->tok[d->i] == '$')
			{
				// expanding here
			}
			
			d->i++;
		}
		current = current->next;
	}

}

void	parser(t_data *d)
{
	p_op_type(d);
	if (d->error != 0)
		return ;
	// lst_print(d->node);
	p_var(d);

	p_syn_check(d);
	if (d->error != 0)
		return ;

	p_quote_exp(d);

	lst_print(d->node);


	(void) d;
	return ;
}