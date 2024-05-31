#include "minishell.h"

void	lex_lstsqueezein(t_tok **current, char *str)
{
	t_tok	*new;
	
	new = lex_lstnew(str);
	if (new == NULL)
		return ;
	new->next = (*current)->next;
	(*current)->next = new;
	return ;
}


void	lex_lst_rmone(t_tok *current)
{
	t_tok *to_delete;
	t_tok *next;

	to_delete = current->next;
	next = current->next->next;
	current->next = next;
	if (to_delete->tok)
		free (to_delete->tok);
	to_delete->next = NULL;
	free (to_delete);
}

char	*lex_strjoin(char const *s1, char const *s2, char deli)
{
	int		k;
	int		len;
	char	*new;

	k = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = (char *) malloc (sizeof(char) * len + 1);
	if (new == NULL)
		return (NULL);
	while (s1[k])
	{
		new[k] = s1[k];
		k++;
	}
	new[k++] = deli;
	while (*(s2))
	{
		new[k++] = *(s2)++;
	}
	new[k] = 0;
	return (new);
}


int	lex_is_separator(char c)
{
	if (c == S || c == T || c == N)
		return (1);
	if (c == '|' || c == '<' || c == '>')
		return (2);
	return (0);
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