#include "minishell.h"

int	lex_is_separator(char c)
{
	if (c == S || c == T || c == N)
		return (1);
	if (c == '|' || c == '<' || c == '>')
		return (2);
	return (0);
}

// quote handling: start quote; end quote; loop through quoted areas
int	lexer_quote_h(t_data *d,t_tok *current)
{
	if (d->q == 0 && (current->tok[d->i] == DBLQUOTE || current->tok[d->i] == SGLQUOTE))
	{
		d->q = current->tok[d->i];
		d->i++;
		return (1);
	}
	else if (d->q != 0 && current->tok[d->i] == d->q)
	{
		d->q = 0;
		d->i++;
		return (1);
	}
	else if (d->q != 0)
	{
		d->i++;
		return (1);
	}
	return (0);
}

int	lex_sep_firstword(t_data *d, t_tok **current)
{
	while (lex_is_separator((*current)->tok[d->i]) == 1)
	{
		(*current)->tok[d->i] = 0;
		d->i++;
	}
	if ((*current)->tok[d->i] == 0)
		return (2);
	if (d->i != 0)
	{
		ft_memmove((*current)->tok, &(*current)->tok[d->i], ft_strlen(&(*current)->tok[d->i]) + 1);
	}
	d->i = 0; //not sure about this; maybe = 0? (used to be =1)
	return (1);
}

int	lex_sep_words(t_data *d, t_tok **current)
{
	while (lex_is_separator((*current)->tok[d->i]) == 1)
	{
		(*current)->tok[d->i] = 0;
		d->i++;
	}
	if ((*current)->tok[d->i] == 0)
		return (2);
	lex_lstsqueezein(&(*current), &(*current)->tok[d->i]);
	(*current) = (*current)->next;
	d->i = 0;
	return (1);

}

int	lex_sep_special(t_data *d, t_tok **current)
{
	if (d->i != 0)
	{
		lex_lstsqueezein(&(*current), &(*current)->tok[d->i]);
		(*current)->tok[d->i] = 0;
		(*current) = (*current)->next;
		d->i = 1;
		if ((*current)->tok[0] == '|' && ((*current)->tok[1] == '<' || (*current)->tok[1] == '>'))
		{
			lex_lstsqueezein(&(*current), &(*current)->tok[d->i]);
			(*current)->tok[d->i] = 0;
			(*current) = (*current)->next;
			d->i = 1;
		}
	}
	if ((*current)->tok[d->i] == '|' && ((*current)->tok[d->i+1] == '<' || (*current)->tok[d->i+1] == '>'))
	{
		d->i++;
		lex_lstsqueezein(&(*current), &(*current)->tok[d->i]);
		(*current)->tok[d->i] = 0;
		(*current) = (*current)->next;
		d->i = 1;
	}
	while (lex_is_separator((*current)->tok[d->i]) == 2)
	{
		d->i++;
	}
	while (lex_is_separator((*current)->tok[d->i]) == 1)
	{
		(*current)->tok[d->i] = 0;
		d->i++;
	}
	if ((*current)->tok[d->i])
	{
		lex_lstsqueezein(&(*current), &(*current)->tok[d->i]);
		(*current)->tok[d->i] = 0;
		(*current) = (*current)->next;
		d->i = 0;
	}
	return (1);

}

int	lexer_separator(t_data *d, t_tok **current)
{
	if (d->q == 0 && lex_is_separator((*current)->tok[d->i]) == 1 && d->i == 0)
	{
		return (lex_sep_firstword(d, current));
	}
	else if (d->q == 0 && lex_is_separator((*current)->tok[d->i]) == 1)
	{
		return (lex_sep_words(d, current));
	}
	else if (d->q == 0 && lex_is_separator((*current)->tok[d->i]) == 2)
	{
		return (lex_sep_special(d, current));
	}
	return (0);
}


void	lexer(t_data *d)
{
	t_tok *current;
	int	s;
	
	init_list2(d, d->input);
	current = d->node;
	d->i = 0;
	s = 0;
	while (current && current->tok)
	{
		if (current->tok[d->i] == 0)
			break;
		if (lexer_quote_h(d, current) == 1)
			continue ;
		s = lexer_separator(d, &current);
		if (s == 1)
			continue ;
		else if (s == 2)
			break ;
		d->i++;
	}
}

// check for unclosed quotes, error if odd number
// doesn't consider quotes of other type after opened quote
int even_quotes(t_data *d)
{
	int	i;
	char	quote;

	i=0;
	quote = 0;
	while (d && d->input && d->input[i])
	{
		if (quote == 0 && (d->input[i] == SGLQUOTE || d->input[i] == DBLQUOTE))
		{
			quote = d->input[i];
		}
		else if (d->input[i] == quote)
		{
			quote = 0;
		}
		i++;
	}
	if (quote == 0)
		return (EVEN);
	else
		return (ODD);
}
