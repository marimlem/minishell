#include "minishell.h"

/* 
void	lex_outside_q(t_data *d, t_tok **current)
{
	if ((*current)->tok[d->i] == 0)
	{
		(*current) = (*current)->next;
		d->i = -1;
		return ;
	}
	else if ((*current)->tok[d->i] == '<' || (*current)->tok[d->i] == '>' || (*current)->tok[d->i] == '|')
	{
		if (d->i > 0)
		{
			lex_lstsqueezein((*current), &(*current)->tok[d->i]);
			(*current)->tok[d->i] = 0;
			(*current) = (*current)->next;
			d->i = 0;
		}
		(*current)->typ = (*current)->tok[d->i++];
		while ((*current)->tok[d->i] == '>' || (*current)->tok[d->i] == '<' || (*current)->tok[d->i] == '|')
			d->i++;
		if ((*current)->tok[d->i] != 0)
		{
			lex_lstsqueezein((*current), &(*current)->tok[d->i]);
			(*current)->tok[d->i] = 0;
			(*current) = (*current)->next;
			d->i = 0;
		}
		return ;
	}
	else if ((*current)->tok[d->i] == SGLQUOTE || (*current)->tok[d->i] == DBLQUOTE)
	{
		d->q = (*current)->tok[d->i];
		if (d->i > 0 && ((*current)->tok[d->i-1] == '|' || (*current)->tok[d->i-1] == '>' || (*current)->tok[d->i-1] == '<')) // if not the first character
		{
			lex_lstsqueezein((*current), &(*current)->tok[d->i+1]);
			(*current)->tok[d->i] = 0;
			(*current) = (*current)->next;
			d->i = -1; 
			return ;
		}
		else if (d->i != 0) 
		{ // case: hello"world" => helloworld
			ft_memmove(&(*current)->tok[d->i], &(*current)->tok[d->i+1], ft_strlen(&(*current)->tok[d->i+1]) + 1);
			// (*current)->tok[ft_strlen(&(*current)->tok[d->i+1]) + 1] = 0;
			(*current)->typ = d->q;
		}
		else if (d->i == 0)
		{
			(*current)->tok = &(*current)->tok[d->i+1];
		}
	}
}


void	lex_inside_q(t_data *d, t_tok **current)
{
	if ((*current)->tok[d->i] == d->q)
	{
		(*current)->typ = d->q;
		d->q = 0;
		if ((*current)->tok[d->i + 1] != 0 && (*current)->tok[d->i + 1] != '|')
		{
			ft_memmove(&(*current)->tok[d->i], &(*current)->tok[d->i+1], ft_strlen(&(*current)->tok[d->i+1]) + 1);
			d->i--;
			return ;
		}
		else if ((*current)->tok[d->i + 1] != 0 && (*current)->tok[d->i + 1] == '|')
		{
			lex_lstsqueezein((*current), &(*current)->tok[d->i+1]);
			(*current)->tok[d->i] = 0;
			(*current) = (*current)->next;
			(*current)->typ = '|';
			d->i = -1;
			return ;
		}
		(*current)->tok[d->i] = 0;
	}
	else if ((*current)->tok[d->i] == 0)
	{// append and remove next node
		(*current)->tok = lex_strjoin((*current)->tok, (*current)->next->tok, ' '); //careful of strjoin leaks
		lex_lst_rmone((*current));
		d->i--;
		return ;
	}
	
}

void	lex_variable(t_data *d, t_tok **current)
{
	int	start;

	start = d->i;
	if ((*current)->tok[d->i] != '$')
		return ;
	d->i++;
	start++;
	while ((*current)->tok[d->i] && (*current)->tok[d->i] != '\'' && ((*current)->tok[d->i] != '\"') && ((*current)->tok[d->i] != ' ')) //add other whitespaces too?
	{
		d->i++;
	}
}

void	quote_merge_2(t_data *d)
{
	t_tok	*current;

	
	current = d->node;
	while (current && current->tok)
	{
//		if (d->q == 0 || d->q == DBLQUOTE)
//			lex_variable(d, &current);

		if (d->q == 0)
			lex_outside_q(d, &current);
		else if (d->q != 0)
			lex_inside_q(d, &current);
		d->i++;
	}

} */
