/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:55:21 by hluo              #+#    #+#             */
/*   Updated: 2024/06/13 20:26:23 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_key_value(t_envlist *envlist, const char *key)
{
	while (envlist)
	{
		if (ft_strcmp(envlist->key, key) == 0)
			return (envlist->value);
		envlist = envlist->next;
	}
	return (NULL);
}

int	ft_key_exists(t_envlist *envlist, char *key, char *value)
{
	while (envlist)
	{
		if (envlist->key != NULL && key != NULL && \
		ft_strcmp(key, envlist->key) == 0)
		{
			free(envlist->value);
			envlist->value = ft_strdup(value);
			if (envlist->value == NULL)
				return (-1);
			envlist->export_only = 0;
			return (0);
		}
		envlist = envlist->next;
	}
	return (1);
}

int	ft_key_exists_for_pe(t_envlist *envlist, char *key, char *value)
{
	char	*valuejoined;

	while (envlist)
	{
		if (ft_strcmp(key, envlist->key) == 0)
		{
			valuejoined = ft_strjoin(envlist->value, value);
			if (valuejoined == NULL)
				return (-1);
			free(envlist->value);
			envlist->value = valuejoined;
			envlist->export_only = 0;
			return (0);
		}
		envlist = envlist->next;
	}
	return (1);
}

int	ft_add_key_and_value(t_envlist **envlist, char *envp, int choice)
{
	char	**after_split;
	int		err;

	err = 0;
	after_split = ft_eqsplit(envp);
	if (after_split == NULL)
		return (1);
	if (choice == 1 && ft_key_exists(*envlist, after_split[0],
			after_split[1]) == 1)
		err = ft_add_list(envlist, after_split[0], after_split[1], 0);
	else if (choice == 2 && ft_key_exists_for_pe(*envlist, after_split[0],
			after_split[1]) == 1)
		err = ft_add_list(envlist, after_split[0], after_split[1], 0);
	else if (choice == 3 && ft_key_exists(*envlist, after_split[0],
			after_split[1]) == 1)
		err = ft_add_list(envlist, after_split[0], after_split[1], 1);
	free_double_array(after_split);
	if (err != 0)
		return (1);
	return (0);
}

int	ft_assign_key_and_value(t_envlist **envlist, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_add_key_and_value(envlist, envp[i], 1) != 0)
		{
			if (i == 0)
			{
				free_list(envlist);
				envlist = NULL;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
