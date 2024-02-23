#include "minishell.h"

int	lex_is_separator(char c)
{
	if (c == S || c == T || c == N)
		return (1);
	if (c == '|' || c == '<' || c == '>')
		return (2);
	return (0);
}

void	lexer(t_data *d)
{
	t_tok *current;
	//new try:
	init_list2(d, d->input);
	current = d->node;
	d->i = 0;
	while (current && current->tok)
	{
		if (current->tok[d->i] == 0)
			break;
		else if (d->q == 0 && (current->tok[d->i] == DBLQUOTE || current->tok[d->i] == SGLQUOTE))
		{
			d->q = current->tok[d->i];
			d->i++;
		}
		else if (d->q != 0 && current->tok[d->i] == d->q)
		{
			d->q = 0;
			d->i++;
		}
		else if (d->q != 0)
			d->i++;
		else if (d->q == 0 && lex_is_separator(current->tok[d->i]) == 1)
		{
			while (lex_is_separator(current->tok[d->i]) == 1)
			{
				current->tok[d->i] = 0;
				d->i++;
			}
			if (current->tok[d->i] == 0)
				break;
			lex_lstsqueezein(&current, &current->tok[d->i]);
			current = current->next;
			d->i = 0;
		}
		else if (d->q == 0 && lex_is_separator(current->tok[d->i]) == 2)
		{
			if (d->i != 0)
			{
				lex_lstsqueezein(&current, &current->tok[d->i]);
				current->tok[d->i] = 0;
				current = current->next;
				d->i = 1;
				if (current->tok[0] == '|' && (current->tok[1] == '<' || current->tok[1] == '>'))
				{
					lex_lstsqueezein(&current, &current->tok[d->i]);
					current->tok[d->i] = 0;
					current = current->next;
					d->i = 1;
				}
			}
			if (current->tok[d->i] == '|' && (current->tok[d->i+1] == '<' || current->tok[d->i+1] == '>'))
			{
				d->i++;
				lex_lstsqueezein(&current, &current->tok[d->i]);
				current->tok[d->i] = 0;
				current = current->next;
				d->i = 1;
			}
			while (lex_is_separator(current->tok[d->i]) == 2)
			{
				d->i++;
			}
			while (lex_is_separator(current->tok[d->i]) == 1)
			{
				current->tok[d->i] = 0;
				d->i++;
			}
			if (current->tok[d->i])
			{
				lex_lstsqueezein(&current, &current->tok[d->i]);
				current->tok[d->i] = 0;
				current = current->next;
				d->i = 0;

			}

		}
		else if (d->q == 0)
			d->i++;

	}
	// lst_print(d->node);
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
