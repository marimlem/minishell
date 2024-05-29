#include "minishell.h"

int	ft_check_arg_for_unset(const char *s)
{
	int	i;

	i = 0;
	if (s[i] && !((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
	{
		if (s[i] == '-' && s[i + 1] == '-' && !s[i + 2])
			return (0);
		else if (s[i] == '-' && s[i + 1])
		{
			ft_putstr_fd("unset: -", 2);
			ft_putchar_fd((char)s[i + 1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			//printf("unset: -%c: invalid option\n", s[i + 1]);
		}
		else if (s[i] == '!' && s[i + 1])
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd((char *)s, 2);
			ft_putstr_fd(": event not found\n", 2);
			//printf("unset: %s: event not found\n", s);
		}
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
