/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:30:43 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/13 18:15:07 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_data *d)
{
	p_op_type(d);
	if (d->error != 0)
		return ;
	p_syn_check(d);
	if (d->error != 0)
		return ;
	init_com(d);
	if (d->error != 0)
		return ;
	fill_com(d, d->node, d->com);
	(void) d;
	return ;
}
