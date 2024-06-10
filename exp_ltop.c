#include "minishell.h"

// moving content to replace stripped quotes
int		ltop_unquoter(t_data *d, char **new)
{
	if (d->q == 0 && ((*new)[d->i] == DBLQUOTE || (*new)[d->i] == SGLQUOTE))
	{
		d->q = (*new)[d->i];
		memmove(&(*new)[d->i], &(*new)[d->i+1], ft_strlen(&(*new)[d->i+1]) + 1);
		(*new)[ft_strlen((*new))] = 0;
		return (1);
	}
	else if(d->q != 0 && d->q == (*new)[d->i]) // doubles up here
	{
		d->q = 0;
		memmove(&(*new)[d->i], &(*new)[d->i+1], ft_strlen(&(*new)[d->i+1]));
		(*new)[ft_strlen((*new)) - 1] = 0;
		return (1);
	}
	return (0);
}

//strips quotes and dollar signs 
int	ltop_dollar(t_data *d, char **new, int exp)
{
	if ((d->q == 0) && (*new)[d->i] == '$'&& ((*new)[d->i + 1] == SGLQUOTE || (*new)[d->i + 1] == DBLQUOTE))
	{
		d->q = (*new)[d->i + 1];
		memmove(&(*new)[d->i], &(*new)[d->i + 2], ft_strlen(&(*new)[d->i])-1);
		if (d->q != (*new)[d->i])
			d->i++;
		return (0);
	}
	else if ((d->q == 0 || d->q == DBLQUOTE) && (*new)[d->i] == '$' && exp == 1)
	{
		d->tmp = (*new);
		expander(d, &(*new)[d->i], (*new));
		if (d->tmp == NULL || d->error != 0)
			return (1); // ERROR is set in expander
		(*new) = d->tmp;
		d->tmp = NULL;
		return (1); 
	}
	d->i++;
	return (0);
}

// heredoc expansion: if heredoc delimiter exp == 0
char	*l_to_p_trans(t_data *d, char *token, int exp)
{
	char	*new;

	d->i = 0;
	d->q = 0;
	new = ft_strdup(token);
	if (new == NULL)
	{
		d->error = ERR_EXP_ALL;
		return (NULL);
	}
	while (new && new[d->i])
	{
		if (ltop_unquoter(d, &new) == 1)
			continue ;
		if (ltop_dollar(d, &new, exp) == 1)
		{
			if (d->error != 0)
				return (NULL);
			continue ;
		}
		else
			continue ;
		d->i++;	
	}
	return (new);
}
