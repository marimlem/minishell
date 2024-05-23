#include "minishell.h"

//Not needed in unset i think
int	ft_check_unset_input(const char *s)
{
	int	i;

	i = 0;
	if (s[i] && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')))
	{
		while (s[i] && ft_isalnum(s[i]) == 1)
			i++;
		if (!s[i])
			return (1);
	}
	return (0);
}

void	ft_rm_node_front(t_envlist **envlist)
{
	t_envlist	*temp;

	temp = (*envlist)->next;
	if ((*envlist)->key)
		free((*envlist)->key);
	if ((*envlist)->value)
		free((*envlist)->value);
	free(*envlist);
	*envlist = temp;
}

void	ft_rm_node(t_envlist **envlist, t_envlist *prev)
{
	t_envlist	*temp;

	temp = (*envlist)->next;
	if ((*envlist)->key)
		free((*envlist)->key);
	if ((*envlist)->value)
		free((*envlist)->value);
	free(*envlist);
	prev->next = temp;
	//write(1, "removing\n", 9);
}

void	ft_unset(t_envlist **envlist, char **arg)
{
	t_envlist	*temp;
	t_envlist	*current;
	int	i;

	i = 0;
	while (arg[++i])
	{
		current = *envlist;
		temp = (*envlist)->next;
		while (temp)
		{
			if (ft_strcmp(arg[i], current->key) == 0)
			{
				ft_rm_node_front(envlist);
				break ;
			}
			else if (ft_strcmp(arg[i], temp->key) == 0)
			{
				ft_rm_node(&temp, current);
				break ;
			}
			current = temp;
			temp = temp->next;
		}
	}
}
