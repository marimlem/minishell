#include "minishell.h"

void	free_2d_array(char **double_array)
{
	int	i;

	i = 0;
	if (!double_array)
		return ;
	while (double_array[i])
	{
		free(double_array[i]);
		i++;
	}
	free(double_array);
	double_array = NULL;
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
	new->next = NULL;
	while (current->next)
		current = current->next;
	current->next = new;
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
		//printf("%s=%s\n", envlist->key, envlist->value);
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

void	free_double_array(char **double_array)
{
	if (double_array)
	{
		if (double_array[0])
			free(double_array[0]);
		if (double_array[1])
			free(double_array[1]);
		free(double_array);
	}
}

// fixed invalid write of size 8
/* char	**ft_eqsplit(char *str)
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
} */

char	**ft_eqsplit(char *str)
{
	int i;
	int str_index;
	char **double_array;

	i = 0;
	str_index = 0;
	double_array = (char **)ft_calloc(3, sizeof(char *));
	if (double_array == NULL)
		return (NULL);

	// Allocate space for the first part
	double_array[0] = (char *)ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (double_array[0] == NULL)
	{
		free_double_array(double_array);
		return (NULL);
	}

	// Allocate space for the second part
	double_array[1] = (char *)ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (double_array[1] == NULL)
	{
		free_double_array(double_array);
		return (NULL);
	}

	// Split the first part
	str_index = ft_split_first_part(str, double_array);

	// Skip the '=' character if it was found
	if (str[str_index] == '=')
		str_index++;

	// Split the second part
	ft_split_second_part(str, double_array, str_index);

	// Null-terminate the array of strings
	double_array[2] = NULL;

	return (double_array);
}