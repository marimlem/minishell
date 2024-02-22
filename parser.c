#include "minishell.h"


// finds and marks operator tokens
// pipe = -124; rdr left = -60; rdr right = -62
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
				current->typ = current->tok[0] * (-1);
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
// pipe cant be first or last
// before a pipe, no other operator can be there ( > |  or | |)
// two in a row check rdr except pipe followed by rdr; rdr must be followed by normal type token
// last token cant be an operator
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
		if (t == 0 && current->typ == '|' * (-1))
		{
			d->error = ERR_PAR_SYN;
			return ;
		}
		else if (current->typ == '|' * (-1) && last < -20)
		{
			d->error = ERR_PAR_SYN;
			return ;
		}
		else if ((current->typ == '>' * (-1) || current->typ == '<' * (-1)) && (last == '>' * (-1) || last == '<' * (-1)))
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
//	char	*new;

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
				expander(d, current);
				printf("***expander triggered***\n");

			}
			
			d->i++;
		}
		current = current->next;
		d->i = 0;
	}

}

void	init_com(t_data *d)
{
	d->com = (t_com *) malloc(sizeof(t_com));
	if (d->com == NULL)
	{
		d->error = ERR_PAR_ALL;
		return ;
	}
	
}

void	parser(t_data *d)
{
	p_op_type(d);
	if (d->error != 0)
		return ;
	p_var(d);
	// if list is completely variable assignment, return

	p_syn_check(d);
	if (d->error != 0)
		return ;
	
	
	//lst_print(d->node);

//	p_quote_exp(d);

	// init_com(d);

	lst_print(d->node);



	(void) d;
	return ;
}