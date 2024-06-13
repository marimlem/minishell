/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:31:19 by lknobloc          #+#    #+#             */
/*   Updated: 2024/06/13 20:12:32 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_path(t_data *d)
{
	t_envlist	*current;

	if (d == NULL || d->env == NULL || *(d->env) == NULL || (*d->env)->key == NULL)
		return (1);
	current = *(d->env);
	while (current && ft_strcmp("PATH", current->key) != 0)
		current = current->next;
	if (current == NULL)
		return (0);
	d->path = ft_split(current->value, ':');
	if (d->path == NULL)
	{
		return (-1);
	}
	return (0);
}

// user input: /usr/bin/ls
// keeps current->file the same, but removes path part from current->arg
int	absolut_path(t_data *d, t_com *current)
{
	char	*ptr;
	int		i;

	i = 1;
	free (current->args[0]);
	current->args[0] = NULL;
	ptr = ft_strrchr(current->file, '/');
	current->args[0] = ft_strdup(&ptr[1]);
	if (current->args[0] == NULL)
	{
		while (current->args[i])
		{
			free (current->args[i]);
			i++;
		}
		return (1);
	}
	(void) d;
	return (0);
}

int	no_path(t_data *d, t_com *current)
{
	char	*tmp;
	char	*t;
	int		i;

	i = 0;
	tmp = NULL;
	while (current->file && d->path && d->path[i])
	{
		t = ft_strjoin(d->path[i], "/");
		if (t == NULL)
		{
			d->error = 1;
			return (1);
		}
		tmp = ft_strjoin(t, current->file);
		free (t);
		t = NULL;
		if (tmp == NULL)
		{
			d->error = 1;
			return (1);
		}
		if (access(tmp, X_OK) == 0)
		{
			free (current->file);
			current->file = NULL;
			current->file = tmp;
			return (0);
		}
		free (tmp);
		tmp = NULL;
		i++;
	}
	return (0);
}

int	setup_cmdpath(t_data *d)
{
	t_com	*current;

	current = d->com;
	while (current)
	{
		current->builtin = 0;
		if (current->file && current->file[0] == '/')
		{
			if (absolut_path(d, current) != 0)
				return (1);
		}
		else if (((is_builtin(current)) >= 1 && (is_builtin(current)) <= 8))
		{
			current->builtin = 1;
		}
		else
		{
			no_path(d, current);
		}
		current = current->next;
	}
	if (d->error != 0)
		return (1);
	return (0);
}

int	relative_path(t_data *d, t_com *current)
{
	free (current->args[0]);
	current->args[0] = NULL;
	current->args[0] = ft_strdup(&current->file[2]);
	if (current->args[0] == NULL)
		return (1);
	free (current->file);
	current->file = ft_strdup(current->args[0]);
	if (current->file == NULL)
		return (1);
	(void) d;
	return (0);
}
