/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:35:19 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 14:36:23 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// quote handling: start quote; end quote; loop through quoted areas
int	lexer_quote_h(t_data *d, t_tok *current)
{
	if (d->q == 0 && (current->tok[d->i] == DBLQUOTE
			|| current->tok[d->i] == SGLQUOTE))
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

void	lexer(t_data *d)
{
	t_tok	*current;
	int		s;

	init_list2(d, d->input);
	current = d->node;
	d->i = 0;
	s = 0;
	while (current && current->tok)
	{
		if (current->tok[d->i] == 0)
			break ;
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
