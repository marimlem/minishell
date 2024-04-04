#include "minishell.h"

int	ft_contains_char(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_add_list(t_envlist **envlist, char *key, char *value)
{
	t_envlist	*current;
	t_envlist	*new;

	if (envlist == NULL || *envlist == NULL)
	{
		*envlist = (t_envlist *)malloc(sizeof(t_envlist));
		(*envlist)->key = ft_strdup(key);
		(*envlist)->value = ft_strdup(value);
		(*envlist)->next = NULL;
		return ;
	}
	current = *envlist;
	new = (t_envlist *)malloc(sizeof(t_envlist));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	ft_print_list(t_envlist *envlist)
{
	while (envlist)
	{
		printf("key: %s\n", envlist->key);
		printf("value: %s\n", envlist->value);
		envlist = envlist->next;
	}
}

//TODO 26 lines has to be shorten
int	ft_split_first_part(char *str, char **double_array)
{
	int	str_index;
	int	new_index;

	str_index = 0;
	new_index = 0;
	if (ft_contains_char(str, '+') == 1)
	{
		while (str[str_index] != '\0' && str[str_index] != '+')
		{
			double_array[0][new_index] = str[str_index];
			str_index++;
			new_index++;
		}
		str_index++;
	}
	else
	{
		while (str[str_index] != '\0' && str[str_index] != '=')
		{
			double_array[0][new_index] = str[str_index];
			str_index++;
			new_index++;
		}
	}
	double_array[0][new_index] = '\0';
	return (str_index);
}

void	ft_split_second_part(char *str, char **double_array, int str_index)
{
	int	new_index;

	new_index = 0;
	while (str[str_index] != '\0')
	{
		double_array[1][new_index] = str[str_index];
		str_index++;
		new_index++;
	}
	double_array[1][new_index] = '\0';
}

//fixed invalid write of size 8
char	**ft_eqsplit(char *str)
{
	int		i;
	int		str_index;
	char	**double_array;

	i = 0;
	str_index = 0;
	double_array = (char **)malloc(sizeof(char *) * 3);
	if (double_array == NULL)
		return (NULL);
	while (i < 2)
	{
		double_array[i] = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (double_array[i] == NULL)
		{
			free(double_array[i]);
			free(double_array);
			return (NULL);
		}
		if (i == 0)
			str_index = ft_split_first_part(str, double_array);
		else
			ft_split_second_part(str, double_array, str_index);
		str_index++;
		i++;
	}
	double_array[i] = NULL;
	return (double_array);
}
