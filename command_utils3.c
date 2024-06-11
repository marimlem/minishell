/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:04:58 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 14:05:21 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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