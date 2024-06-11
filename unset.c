#include "minishell.h"

int	ft_check_arg_for_unset(const char *s)
{
	int	i;

	i = 0;
	if (s[i] && !((s[i] >= 'a' && s[i] <= 'z') || \
	(s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
	{
		if (s[i] == '-' && s[i + 1] == '-' && !s[i + 2])
			return (0);
		else if (s[i] == '-' && s[i + 1])
		{
			ft_putstr_fd("unset: -", 2);
			ft_putchar_fd((char)s[i + 1], 2);
			ft_putstr_fd(": invalid option\n", 2);
		}
		else if (s[i] == '!' && s[i + 1])
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd((char *)s, 2);
			ft_putstr_fd(": event not found\n", 2);
		}
		return (1);
	}
	return (0);
}

void	ft_rm_node_front(t_envlist **envlist)
{
	t_envlist	*temp;

	if (envlist == NULL)
		return ;
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

	if (envlist == NULL)
		return ;
	temp = (*envlist)->next;
	if ((*envlist)->key)
		free((*envlist)->key);
	if ((*envlist)->value)
		free((*envlist)->value);
	free(*envlist);
	prev->next = temp;
}

void	remove_node(char **arg, int i, t_envlist **envlist)
{
	t_envlist	*temp;
	t_envlist	*current;

	if (envlist == NULL)
		return ;
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

void	ft_unset(t_envlist **envlist, char **arg)
{
	int	i;

	if (envlist == NULL)
		return ;
	i = 0;
	while (arg[++i])
	{
		remove_node(arg, i, envlist);
	}
}
