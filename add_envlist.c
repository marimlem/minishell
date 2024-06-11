#include "minishell.h"

void	add_first(t_envlist **envlist, char *key, char *value)
{
	t_envlist	*current;

	current = *envlist;
	if (current->key == NULL && current->value == NULL && current->next == NULL)
	{
		current->key = ft_strdup(key);
		current->value = ft_strdup(value);
		if (current->key == NULL || current->value == NULL)
		{
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		current->next = NULL;
		return ;
	}
}

void	add_last(t_envlist *envlist, char *key, char *value)
{
	t_envlist	*current;
	t_envlist	*new;

	new = (t_envlist *)ft_calloc(1, sizeof(t_envlist));
	if (new == NULL)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (new->key == NULL || new->value == NULL)
	{
		free(new->key);
		free(new->value);
		free(new);
		return ;
	}
	current = envlist;
	while (current->next)
		current = current->next;
	current->next = new;
	new->next = NULL;
}

void	ft_add_list(t_envlist **envlist, char *key, char *value)
{
	t_envlist	*current;

	current = *envlist;
	if (!current || (current->key == NULL && \
	current->value == NULL && current->next == NULL))
		add_first(envlist, key, value);
	else
		add_last(current, key, value);
}

void	ft_print_list(t_data *d, t_envlist *envlist)
{
	d->exit_code = 0;
	while (envlist != NULL)
	{
		ft_putstr_fd((char *)envlist->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd((char *)envlist->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		envlist = envlist->next;
	}
}
