/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:37:34 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 12:26:39 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tok_op_handling(t_data *d, t_tok **current, int *t)
{
	if (!*current)
		return (0);
	if (ft_strlen((*current)->tok) > 2)
	{
		d->error = ERR_PAR_SYN;
		return (1);
	}
	else if (((*current)->tok[1] && (*current)->tok[0] == '|')
		|| ((*current)->tok[1] && (*current)->tok[0] != (*current)->tok[1]))
	{
		d->error = ERR_PAR_SYN;
		return (1);
	}
	else if (ft_strlen((*current)->tok) == 1 || ((*current)->tok[1]
			&& (*current)->tok[0] == (*current)->tok[1]))
	{
		if ((*current)->tok[0] == '|')
			*t = 1;
		(*current)->typ = (*current)->tok[0] * (-1);
		(*current) = (*current)->next;
		return (2);
	}
	return (0);
}

// finds and marks operator tokens
// pipe = -124; rdr left = -60; rdr right = -62
void	p_op_type(t_data *d)
{
	t_tok	*current;
	int		t;
	int		p;

	current = d->node;
	t = 1;
	d->i = 0;
	p = 0;
	while (current && current->tok)
	{
		if ((current->tok[0] == '>' || current->tok[0] == '<'
				|| current->tok[0] == '|'))
		{
			p = tok_op_handling(d, &current, &t);
			if (p == 1)
				return ;
			else if (p == 2)
				continue ;
		}
		else
			current->typ = t++;
		current = current->next;
	}
}

// checks if operators are in syntactically good order 
	// (not first, not last, not two in a row)
// pipe cant be first or last
// before a pipe, no other operator can be there ( > |  or | |)
// two in a row check rdr except pipe followed by rdr; rdr must be followed
	// by normal type token
// last token cant be an operator
void	p_syn_check(t_data *d)
{
	t_tok	*current;
	int		t;
	int		last;

	t = 0;
	last = 0;
	current = d->node;
	while (current && current->tok)
	{
		if ((t == 0 && current->typ == '|' * (-1))
			|| (current->typ == '|' * (-1) && last < -20)
			|| ((current->typ == '>' * (-1) || current->typ == '<' * (-1))
			&& (last == '>' * (-1) || last == '<' * (-1))))
		{
			d->error = ERR_PAR_SYN;
			return ;
		}
		last = current->typ;
		t++;
		current = current->next;
	}
	if (last < -10)
		d->error = ERR_PAR_SYN;
}
