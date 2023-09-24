/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:02:02 by lknobloc          #+#    #+#             */
/*   Updated: 2022/11/06 17:08:50 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i - 1] != c)
			count++;
	}
	return (count);
}

static int	ft_wlen(const char *s, char c)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	*my_arrmall(char c, char const *s, int i, char **mat)
{
	char	*arr;
	int		k;

	k = 0;
	arr = (char *) ft_calloc(ft_wlen(&s[i], c) + 1, + sizeof(char));
	if (arr == NULL)
	{
		while (mat[k])
			free (mat[k++]);
		free (mat);
		return (NULL);
	}
	return (arr);
}

char	**fill_arr(char const *s, char **arr, int len, char c)
{
	int	i;
	int	k;
	int	x;

	i = 0;
	k = 0;
	x = 0;
	while (x < len)
	{
		arr[x] = my_arrmall(c, s, i, arr);
		if (arr[x] == NULL)
			return (NULL);
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			arr[x][k++] = s[i++];
		x++;
		k = 0;
	}
	return (&arr[0]);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		len;

	if (!s)
		return (NULL);
	len = ft_word(s, c);
	array = (char **) malloc((len + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = fill_arr(s, array, len, c);
	if (array == NULL)
		return (NULL);
	array[len] = NULL;
	return (&array[0]);
}
