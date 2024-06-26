/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:24:49 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/11 18:05:06 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envlist(t_envlist **envlist)
{
	(*envlist)->key = NULL;
	(*envlist)->value = NULL;
	(*envlist)->next = NULL;
	(*envlist)->export_only = 0;
}

void	init_null(t_data *d)
{
	d->input = NULL;
	d->node = NULL;
	d->com = NULL;
	d->tmp = NULL;
	d->fd = NULL;
	d->old_fd = NULL;
	d->i = 0;
	d->q = 0;
	d->error = 0;
	d->p = NULL;
	d->path = NULL;
	d->hd_path = NULL;
	d = NULL;
}

int	raise_shlvl(char **envp)
{
	int	i;
	int	lvl;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			lvl = ft_atoi(&envp[i][6]);
			if (lvl >= 9)
			{
				ft_putstr_fd("minishell error: shell-level too high: ", 2);
				ft_putnbr_fd(lvl, 2);
				ft_putstr_fd("\n", 2);
				return (lvl);
			}
			else
				envp[i][6] = envp[i][6] + 1;
			break ;
		}
		i++;
	}
	if (!envp || !envp[i])
		return (1);
	return (0);
}
