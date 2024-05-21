#include "minishell.h"

char	*ft_find_key_value(t_envlist *envlist, const char *key)
{
	while (envlist)
	{
		// TODO change
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
		if (envlist->key != NULL && key != NULL && ft_strcmp(key, envlist->key) == 0)
		{
			free(envlist->value);
			envlist->value = ft_strdup(value);
			if (envlist->value == NULL)
				return (-1);
			return (0);
		}
		envlist = envlist->next;
	}
	return (1);
}

/* int	ft_key_exists(t_envlist *envlist, char *key, char *value)
{
	envlist = NULL;
	while (envlist != NULL)
	{
		if (envlist->key != NULL && key != NULL)
		{ // Check for NULL pointers
			if (ft_strcmp(key, envlist->key) == 0)
			{                               // Use strcmp for string comparison
				if (envlist->value != NULL)
					// Check if envlist->value is initialized
					free(envlist->value);  
						// Free existing value if initialized
				envlist->value = ft_strdup2(value);
				if (envlist->value == NULL)
					return (-1);
				return (0);
			}
		}
		envlist = envlist->next;
	}
	return (1);
} */

// TODO free
int	ft_key_exists_for_PE(t_envlist *envlist, char *key, char *value)
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
			return (0);
		}
		envlist = envlist->next;
	}
	return (1);
}

void	ft_add_key_and_value(t_envlist **envlist, char *envp, int choice)
{
	char	**after_split;

	after_split = ft_eqsplit(envp);
	if (choice == 1 && ft_key_exists(*envlist, after_split[0],
			after_split[1]) == 1)
		ft_add_list(envlist, after_split[0], after_split[1]);
	else if (choice == 2 && ft_key_exists_for_PE(*envlist, after_split[0],
			after_split[1]) == 1)
		ft_add_list(envlist, after_split[0], after_split[1]);
	free_double_array(after_split);
}

void	ft_assign_key_and_value(t_envlist **envlist, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		ft_add_key_and_value(envlist, envp[i], 1);
		i++;
	}
}