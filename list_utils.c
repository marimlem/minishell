/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:30:39 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 14:34:33 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_lst_del(t_tok *lst)
{
	t_tok	*c;

	c = lst;
	if (c)
	{
		lex_lst_del(c->next);
		if (c->tok)
			free (c->tok);
		c->next = NULL;
		free (c);
	}
}

void	com_lst_del_two(t_com *c)
{
	int	i;

	i = 0;
	com_lst_del(c->next);
	if (c->file)
		free (c->file);
	c->file = NULL;
	if (c->args)
	{
		while (c->args[i])
		{
			free (c->args[i]);
			c->args[i++] = NULL;
		}
		free (c->args);
		c->args = NULL;
	}
}

void	com_lst_del(t_com *lst)
{
	t_com	*c;
	int		i;

	i = 0;
	c = lst;
	if (c)
	{
		com_lst_del_two(c);
		i = 0;
		if (c->rdr)
		{
			while (c->rdr[i])
			{
				free (c->rdr[i]);
				c->rdr[i++] = NULL;
			}
			free (c->rdr);
			c->rdr = NULL;
		}
		c->next = NULL;
		free (c);
	}
}

void	envlist_del(t_envlist *env)
{
	t_envlist	*e;

	e = env;
	if (e)
	{
		envlist_del(e->next);
		if (e->key)
			free (e->key);
		e->key = NULL;
		if (e->value)
			free (e->value);
		e->value = NULL;
		e->next = NULL;
		free (e);
	}
}
