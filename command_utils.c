/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:30:38 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 14:05:24 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	rdr_append(t_data *d, t_tok *current, t_com *c_cur, int r)
{
	c_cur->rdr[r] = ft_strdup(current->tok);
	if (c_cur->rdr[r++] == NULL)
	{
		d->error = ERR_PAR_ALL;
		return (r);
	}
	if (c_cur->rdr[r - 1][0] == '<' && c_cur->rdr[r - 1][1] == '<')
		c_cur->rdr[r] = heredoc_exp(d, current->next->tok, c_cur, r - 1);
	else
		c_cur->rdr[r] = l_to_p_trans(d, current->next->tok, 1);
	if (c_cur->rdr[r] == NULL)
	{
		d->error = ERR_PAR_ALL;
		return (r);
	}
	r++;
	return (r);
}

int	arg_append(t_data *d, t_tok *current, t_com *c_cur, int a)
{
	if (a == 0)
	{
		c_cur->file = l_to_p_trans(d, current->tok, 1);
		if (c_cur->file == NULL)
		{
			d->error = ERR_PAR_ALL;
			return (a);
		}
		c_cur->args[a] = ft_strdup(c_cur->file);
		if (c_cur->args[a] == NULL)
			d->error = ERR_PAR_ALL;
	}
	else
	{
		c_cur->args[a] = l_to_p_trans(d, current->tok, 1);
		if (c_cur->args[a] == NULL)
		{
			d->error = ERR_PAR_ALL;
			return (a);
		}
	}
	a++;
	return (a);
}

void	fill_com_loop(t_data *d, t_tok *current, t_com *c_cur)
{
	int		r;
	int		a;

	a = 0;
	r = 0;
	while (current && current->tok && d->error == 0)
	{
		if (current->typ == PIPE * (-1))
		{
			com_lstsqueezein(&c_cur);
			fill_com(d, current->next, c_cur->next);
			return ;
		}
		else if (current->typ < 0)
		{
			r = rdr_append(d, current, c_cur, r);
			current = current->next->next;
		}
		else if (current->typ > 0)
		{
			a = arg_append(d, current, c_cur, a);
			current = current->next;
		}
	}
}

void	fill_com(t_data *d, t_tok *t_node, t_com *c_node)
{
	t_tok	*current;
	t_com	*c_cur;

	current = t_node;
	c_cur = c_node;
	setup_coms(d, t_node, c_node);
	if (c_cur->rdr == NULL || c_cur->args == NULL)
	{
		d->error = ERR_PAR_ALL;
		return ;
	}
	fill_com_loop(d, current, c_cur);
	if (d->error != 0)
		return ;
	if (fill_file_ifnecessary(d) != 0)
		d->error = 1;
}
