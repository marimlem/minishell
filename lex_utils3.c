#include "minishell.h"

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

void	lex_sep_special_mid(t_data *d, t_tok **current)
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

int	lex_sep_special(t_data *d, t_tok **current)
{
	if (d->i != 0)
		lex_sep_special_mid(d, current);
	if ((*current)->tok[d->i] == '|' && ((*current)->tok[d->i+1] == '<' || (*current)->tok[d->i+1] == '>'))
	{
		d->i++;
		lex_lstsqueezein(&(*current), &(*current)->tok[d->i]);
		(*current)->tok[d->i] = 0;
		(*current) = (*current)->next;
		d->i = 1;
	}
	while (lex_is_separator((*current)->tok[d->i]) == 2)
		d->i++;
	while (lex_is_separator((*current)->tok[d->i]) == 1)
		(*current)->tok[d->i++] = 0;
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