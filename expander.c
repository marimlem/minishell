#include "minishell.h"

int	is_variable(t_var *node, char *find)
{
	if (node && node->key == NULL)
		return (0);
	if (is_variable(node->next, find) == 1)
		return (1);
	else
	{
		if (ft_strncmp(node->key, find, ft_strlen(node->key) + ft_strlen(find)) == 0)
			return (1);
		return (0);
	}
	
}

void	expand_var(t_data *d, char *new)
{
	(void) d;
	(void) new;
	return ;
}

void 	expand_empty(t_data *d, char *new)
{
	int	i;

	i = 1;
	if (new[i] && ft_isdigit(new[i]))
	{
		ft_memmove(&d->tmp[d->i], &new[i+1], ft_strlen(&new[i + 1]) + 1);
		return ;
	}
	while (new[i] && (ft_isdigit(new[i]) || ft_isalpha(new[i]) || new[i] == '_'))//(lex_is_separator(new[i]) == 0 || (new[i] == SGLQUOTE || new[i] == DBLQUOTE)))
	{
		i++;
	}
	if (new[i])
		ft_memmove(&d->tmp[d->i], &new[i], ft_strlen(&new[i]) + 1);
	else
		d->tmp[d->i] = 0;

	(void) d;
	return ;
}

void 	expand_exitstatus(t_data *d) // not as simple unfortunately, will need to allocate space for longer numbers
{
	char	*code;
	char	*exp;
	int		len;

	code = ft_itoa(d->exit_code);
	if (code == NULL)
	{
		d->error = 301;
		return ;
	}
	len = ft_strlen(code);
	exp = (char *) ft_calloc(len + ft_strlen(d->tmp), sizeof(char));
	if (exp ==NULL)	
	{
		free (code);
		code = NULL;
		d->error = 301;
		return ;
	}
	ft_memmove(exp, d->tmp, d->i);
	ft_memmove(&exp[d->i], code, len);
	if (d->tmp[d->i + 2] != 0)
		ft_memmove(&exp[ft_strlen(code) + d->i], &d->tmp[d->i + 2], ft_strlen(&d->tmp[d->i + 2]));
	else
	{
		while (d->tmp[d->i + len])
		{
			d->tmp[d->i + len] = 0 ;
			len ++;
		}
	}
	d->i = d->i + ft_strlen(code);
	free(d->tmp);
	d->tmp = exp;
	return ;
}

int	exp_varlen(char *new)
{
	int	i;

	i = 1;
	if (new[i] && ft_isdigit(new[i]))
		return (i);
	else
	{
		while (new[i] && (ft_isdigit(new[i]) || ft_isalpha(new[i]) || new[i] == '_'))//(lex_is_separator(new[i]) == 0 || (new[i] == SGLQUOTE || new[i] == DBLQUOTE)))
			i++;
	}
	return (i);
}

int 	expand_env(t_data *d, char *new, char *str)
{
	t_envlist *node;
	int i;
	char	*exp;

	node = *(d->env);
	i = exp_varlen(new);
	while (node && node->key)
	{
		if ((int) ft_strlen(node->key) + 1 == i && ft_strncmp(node->key, &new[1], i - 1) == 0)
		{
			exp = (char *) ft_calloc(sizeof(char), ft_strlen(d->tmp) + ft_strlen(node->value));
			if (exp == NULL)
			{
				d->error = 301;
				return (-1); // alloc error
			}
			ft_memmove(exp, str, d->i);
			ft_memmove(&exp[d->i], node->value, ft_strlen(node->value));
			ft_memmove(&exp[ft_strlen(node->value) + d->i], &str[d->i + i], ft_strlen(&str[d->i + i]));
			d->i = d->i + ft_strlen(node->value);
			free(d->tmp);
			d->tmp = exp;
			return (1);
		}
		node = node->next;
	}
	return (0);
}

void	expand_shellname(t_data *d)
{
	char	*exp;

	exp = (char *) ft_calloc(sizeof(char), ft_strlen(d->tmp) + 13);
	if (exp == NULL)
	{
		d->error = 301; //alloc error
		return ;
	}
	ft_memmove(exp, d->tmp, d->i);
	ft_memmove(&exp[d->i], "minishell <3", 12);
	ft_memmove(&exp[d->i + 12], &d->tmp[d->i + 2], ft_strlen(&d->tmp[d->i + 2]));
	free (d->tmp);
	d->tmp = exp;
	d->i += 12;
}

void	expander(t_data *d, char *new, char *str)
{
	int	i;

	i = 0;
	if (!new[i + 1])
	{
		d->i++;
		return ;
	}
	if (new[i + 1] == '0')
	{
		expand_shellname(d);
		return ;
	}
	if (new[i + 1] == '?')
	{
		expand_exitstatus(d);
		return ;
	}
	else if (!ft_isdigit(new[i + 1]) && !ft_isalpha(new[i + 1]) && new[i + 1] != '_')
	{
		d->i++;
		return ;
	}
	if (expand_env(d, new, str) != 0)
		return ;
	else
		expand_empty(d, new);
}

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
		memmove(&(*new)[d->i], &(*new)[d->i + 2], ft_strlen(&(*new)[d->i]));
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
	return (0);
}

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
		d->i++;	
	}
	return (new);
}
