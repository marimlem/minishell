#include "minishell.h"

void	free_2d_array(char **split_str)
{
	int	i;

	i = 0;
	if (!split_str)
		return ;
	while (split_str[i])
	{
		free(split_str[i]);
		i++;
	}
	free(split_str);
	split_str = NULL;
}

void	free_list(t_envlist **envlist)
{
	t_envlist	*current;
	t_envlist	*next;

	current = *envlist;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	free(envlist);
}

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

	current = *envlist;
	if (current->key == NULL && current->value == NULL && current->next == NULL)
	{
		current->key = ft_strdup2(key);
		current->value = ft_strdup2(value);
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
	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (new == NULL)
		return ;
	new->key = ft_strdup2(key);
	new->value = ft_strdup2(value);
	if (new->key == NULL || new->value == NULL)
	{
		free(new->key);
		free(new->value);
		free(new);
		return ;
	}
	new->next = NULL;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	ft_print_list(t_envlist *envlist)
{
	while (envlist != NULL)
	{
		printf("%s=%s\n", envlist->key, envlist->value);
		envlist = envlist->next;
	}
}

// TODO 26 lines has to be shorten
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

// fixed invalid write of size 8
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
