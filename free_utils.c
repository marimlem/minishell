/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:48:00 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/13 20:14:51 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_part_two(t_data *d)
{
	int	i;

	i = 0;
	if (d->p)
	{
		while (d->p[i])
		{
			free (d->p[i]);
			d->p[i++] = NULL;
		}
		free (d->p);
		d->p = NULL;
	}
	if (d->hd_path)
	{
		unlink(d->hd_path);
		free (d->hd_path);
		d->hd_path = NULL;
	}
}

void	clean_part_one(t_data *d)
{
	int	i;

	i = 0;
	lex_lst_del(d->node);
	com_lst_del(d->com);
	if (d->input)
		free (d->input);
	if (d->tmp)
		free (d->tmp);
	d->error = 0;
	d->i = 0;
	d->q = 0;
	if (d->fd)
		free (d->fd);
	if (d->old_fd)
		free(d->old_fd);
	if (d->path)
	{
		while (d->path[i])
		{
			free(d->path[i]);
			d->path[i++] = NULL;
		}
		free (d->path);
	}
}

void	free_n_clean(t_data *d, int b)
{
	if (d == NULL)
		return ;
	clean_part_one(d);
	clean_part_two(d);
	if (b == 0)
		return ;
	if (d->env)
		free_list(d->env);
	if (d)
		free (d);
	d = NULL;
}

void	free_double_array(char **double_array)
{
	if (double_array)
	{
		if (double_array[0])
		{
			free(double_array[0]);
			double_array[0] = NULL;
		}
		if (double_array[1])
		{
			free(double_array[1]);
			double_array[1] = NULL;
		}
		free(double_array);
		double_array = NULL;
	}
}

void	free_list(t_envlist **envlist)
{
	t_envlist	*current;
	t_envlist	*next;

	if (envlist == NULL)
		return ;
	current = *envlist;
	while (current != NULL)
	{
		next = current->next;
		if (current->key != NULL)
			free(current->key);
		current->key = NULL;
		if (current->value != NULL)
			free(current->value);
		current->value = NULL;
		if (current)
			free(current);
		current = NULL;
		current = next;
	}
	free(envlist);
	envlist = NULL;
}
