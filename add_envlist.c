/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_envlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:54:57 by hluo              #+#    #+#             */
/*   Updated: 2024/06/13 20:26:41 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_first(t_envlist **envlist, char *key, char *value)
{
	t_envlist	*current;

	if (envlist == NULL || *envlist == NULL)
		return (1);
	current = *envlist;
	if (current->key == NULL && current->value == NULL && current->next == NULL)
	{
		current->key = ft_strdup(key);
		current->value = ft_strdup(value);
		if (current->key == NULL || current->value == NULL)
		{
			free(current->key);
			free(current->value);
			current->key = NULL;
			current->value = NULL;
			free(current);
			current = NULL;
			free (*envlist);
			*envlist = NULL;
			return (1);
		}
		current->next = NULL;
	}
	return (0);
}

int	add_last(t_envlist *envlist, char *key, char *value)
{
	t_envlist	*current;
	t_envlist	*new;

	new = (t_envlist *)ft_calloc(1, sizeof(t_envlist));
	if (new == NULL)
		return (1);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (new->key == NULL || new->value == NULL)
	{
		free(new->key);
		free(new->value);
		free(new);
		return (1);
	}
	current = envlist;
	while (current->next)
		current = current->next;
	current->next = new;
	new->next = NULL;
	return (0);
}

int	ft_add_list(t_envlist **envlist, char *key, char *value, \
int export_check)
{
	t_envlist	*current;

	current = *envlist;
	if (!current || (current->key == NULL && \
	current->value == NULL && current->next == NULL))
	{
		if (add_first(envlist, key, value) != 0)
			return (1);
	}
	else
	{
		if (add_last(current, key, value) != 0)
			return (1);
	}
	while (current->next)
		current = current->next;
	if (export_check == 1)
		current->export_only = 1;
	else
		current->export_only = 0;
	return (0);
}

void	ft_print_list(t_data *d, t_envlist *envlist)
{
	d->exit_code = 0;
	while (envlist != NULL)
	{
		if (envlist->export_only == 0)
		{
			ft_putstr_fd((char *)envlist->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd((char *)envlist->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		envlist = envlist->next;
	}
}
