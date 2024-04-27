/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluo <hluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:30:41 by hluo              #+#    #+#             */
/*   Updated: 2024/04/04 17:00:07 by hluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_words(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c && j == 0)
		{
			j = 1;
			i++;
		}
		else if (*s == c)
			j = 0;
		s++;
	}
	return (i);
}

static char	*duplicate_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_return(char **d, size_t j)
{
	d[j] = 0;
	return (d);
}

char	**ft_split2(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**d;

	if (s == 0)
		return (0);
	d = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (d == 0)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			d[j++] = duplicate_word(s, index, i);
			index = -1;
		}
		i++;
	}
	return (ft_return(d, j));
}

/*int	main(void)
{
	char	ptr[] = "             ";
	char	c;
	char	*final;

	c = ' ';
	final = (char *)ft_split(ptr, c);
	printf("%s\n", final);
	return (0);
}*/
