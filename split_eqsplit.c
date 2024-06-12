/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_eqsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluo <hluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:55:27 by hluo              #+#    #+#             */
/*   Updated: 2024/06/12 19:55:27 by hluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_split_first_part(char *str, char **double_array)
{
	int	str_index;
	int	new_index;

	str_index = 0;
	new_index = 0;
	if (!str || !double_array || !double_array[0])
		return (-1);
	while (str[str_index] != '\0' && \
	str[str_index] != '+' && str[str_index] != '=')
	{
		double_array[0][new_index] = str[str_index];
		str_index++;
		new_index++;
	}
	double_array[0][new_index] = '\0';
	if (str[str_index] != '\0')
		str_index++;
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

char	**allocate_double_array(size_t len)
{
	char	**double_array;

	double_array = (char **)ft_calloc(3, sizeof(char *));
	if (!double_array)
		return (NULL);
	double_array[0] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!double_array[0])
	{
		free(double_array);
		return (NULL);
	}
	double_array[1] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!double_array[1])
	{
		free(double_array[0]);
		free(double_array);
		return (NULL);
	}
	return (double_array);
}

char	**ft_eqsplit(char *str)
{
	char	**double_array;
	int		str_index;

	double_array = allocate_double_array(ft_strlen(str));
	if (double_array == NULL)
		return (NULL);
	str_index = ft_split_first_part(str, double_array);
	if (str[str_index] == '=')
		str_index++;
	ft_split_second_part(str, double_array, str_index);
	double_array[2] = NULL;
	return (double_array);
}
