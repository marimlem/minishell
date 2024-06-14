/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:04:33 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/13 22:08:48 by lknobloc         ###   ########.fr       */
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
	if (!ft_strchr(tok, '\'') && !ft_strchr(tok, '\"'))
	{
		return (ft_strdup(tok));
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
