#include "minishell.h"

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
		i++;
	if (new[i])
		ft_memmove(&d->tmp[d->i], &new[i], ft_strlen(&new[i]) + 1);
	else
		d->tmp[d->i] = 0;

	return ;
}

int	setup_ext(t_data *d, char **code, char **exp, int *len)
{
	(*code) = ft_itoa(d->exit_code % 255);
	if ((*code) == NULL)
	{
		d->error = 231;
		return (1);
	}
	*len = ft_strlen((*code));
	(*exp) = (char *) ft_calloc(*len + ft_strlen(d->tmp), sizeof(char));
	if ((*exp) ==NULL)	
	{
		free ((*code));
		*code = NULL;
		d->error = 231;
		return (1);
	}
	return (0);
}

void 	expand_exitstatus(t_data *d)
{
	char	*code;
	char	*exp;
	int		len;

	// ft_putstr_fd("{...", 2);
	// ft_putnbr_fd(d->exit_code, 2);
	// ft_putstr_fd("... expander}\n", 2);
	if (setup_ext(d, &code, &exp, &len) != 0)
		return ;
	ft_memmove(exp, d->tmp, d->i);
	ft_memmove(&exp[d->i], code, len);
	if (d->tmp[d->i + 2] != 0)
		ft_memmove(&exp[ft_strlen(code) + d->i], &d->tmp[d->i + 2], ft_strlen(&d->tmp[d->i + 2]));
	else
	{
		while (d->tmp[d->i + len -1])
		{
			d->tmp[d->i + len -1] = 0 ;
			len ++;
		}
	}
	d->i = d->i + ft_strlen(code);
	free(d->tmp);
	d->tmp = exp;
	if (code)
		free (code);
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
