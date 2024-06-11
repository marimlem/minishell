/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:57:54 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 16:01:47 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_empty(t_data *d, char *new)
{
	int	i;

	i = 1;
	if (new[i] && ft_isdigit(new[i]))
	{
		ft_memmove(&d->tmp[d->i], &new[i + 1], ft_strlen(&new[i + 1]) + 1);
		return ;
	}
	while (new[i] && (ft_isdigit(new[i]) || ft_isalpha(new[i])
			|| new[i] == '_'))
		i++;
	if (new[i])
		ft_memmove(&d->tmp[d->i], &new[i], ft_strlen(&new[i]) + 1);
	else
		d->tmp[d->i] = 0;
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
		while (new[i] && (ft_isdigit(new[i]) || ft_isalpha(new[i])
				|| new[i] == '_'))
			i++;
	}
	return (i);
}

int	malloc_dat_exp(t_data *d, char **exp, char *value)
{
	*exp = (char *) ft_calloc(sizeof(char),
			ft_strlen(d->tmp) + ft_strlen(value));
	if (exp == NULL)
	{
		d->error = 301;
		return (1);
	}
	return (0);
}

int	expand_env(t_data *d, char *new, char *str)
{
	t_envlist	*node;
	int			i;
	char		*exp;

	node = *(d->env);
	i = exp_varlen(new);
	while (node && node->key)
	{
		if ((int) ft_strlen(node->key) + 1 == i
			&& ft_strncmp(node->key, &new[1], i - 1) == 0)
		{
			if (malloc_dat_exp(d, &exp, node->value) == 1)
				return (-1);
			ft_memmove(exp, str, d->i);
			ft_memmove(&exp[d->i], node->value, ft_strlen(node->value));
			ft_memmove(&exp[ft_strlen(node->value) + d->i], &str[d->i + i],
				ft_strlen(&str[d->i + i]));
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
		d->error = 301;
		return ;
	}
	ft_memmove(exp, d->tmp, d->i);
	ft_memmove(&exp[d->i], "minishell <3", 12);
	ft_memmove(&exp[d->i + 12], &d->tmp[d->i + 2],
		ft_strlen(&d->tmp[d->i + 2]));
	free (d->tmp);
	d->tmp = exp;
	d->i += 12;
}

void	expander(t_data *d, char *new, char *str)
{
	int	i;

	i = 0;
	if (!new[i + 1])
		d->i++;
	else if (new[i + 1] == '0')
		expand_shellname(d);
	else if (new[i + 1] == '?')
		expand_exitstatus(d);
	else if (!ft_isdigit(new[i + 1]) && !ft_isalpha(new[i + 1])
		&& new[i + 1] != '_')
		d->i++;
	else if (expand_env(d, new, str) != 0)
		return ;
	else
		expand_empty(d, new);
}
