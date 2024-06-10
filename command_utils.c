/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:30:38 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/10 20:33:00 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	*com_lstnew(void)
{
	t_com	*list;

	list = (t_com *) malloc(sizeof(t_com) * 1);
	if (list == NULL)
		return (NULL);
	list->pid = 0;
	list->status = 0;
	list->file = NULL;
	list->args = NULL;
	list->rdr = NULL;
	list->next = NULL;
	return (list);
}

void	com_lstsqueezein(t_com **current)
{
	t_com	*new;

	new = com_lstnew();
	if (new == NULL)
		return ;
	new->next = (*current)->next;
	(*current)->next = new;
	return ;
}

void	init_com(t_data *d)
{
	d->com = com_lstnew();
	if (d->com == NULL)
	{
		d->error = ERR_PAR_ALL;
		return ;
	}
}

char	*heredoc_exp(t_data *d, char *tok, t_com *current, int r)
{
	if (!strchr(tok, '\'') && !strchr(tok, '\"'))
	{
		return (strdup(tok));
	}
	current->rdr[r][2] = SGLQUOTE;
	return (l_to_p_trans(d, tok, 0));
}

// count rdr and args until pipe
// < 0 means rdr // bigger than zero means arg
// dec == 1 means count rdr // dec != 1 means count args
int	count_type(t_data *d, t_tok *t_node, int dec)
{
	t_tok	*current;
	int		count;

	current = t_node;
	count = 0;
	while (current && current->typ != '|' * (-1))
	{
		if (dec == 1 && current->typ < 0)
		{
			count++;
			if (current->next)
				current = current->next;
			else
			{
				d->error = 21;
				return (-1);
			}
		}
		else
			count ++;
		current = current->next;
	}
	return (count);
}

void	alloc_coms(t_com *c_cur, int rdr_c, int arg_c)
{
	if (rdr_c != 0)
	{
		c_cur->rdr = (char **) ft_calloc((rdr_c * 2) + 1, sizeof(char *));
	}
	c_cur->args = (char **) ft_calloc(arg_c + 1, sizeof(char *));
}

void	setup_coms(t_data *d, t_tok *t_node, t_com *c_node)
{
	int		rdr_c;
	int		arg_c;

	rdr_c = count_type(d, t_node, 1);
	arg_c = count_type(d, t_node, 2);
	if (rdr_c == -1)
		return ;
	alloc_coms(c_node, rdr_c, arg_c);
}

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

int	fill_file_ifnecessary(t_data *d)
{
	t_com	*current;

	current = d->com;
	while (current)
	{
		if (current->file == NULL)
			current->file = ft_strdup("");
		if (current->file == NULL)
			return (1);
		current = current->next;
	}
	return (0);
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
