/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:07:43 by lknobloc          #+#    #+#             */
/*   Updated: 2023/02/16 18:07:44 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	*gnl_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (NULL);
	i = 0;
	if (nmemb >= 2147483647 || size >= 2147483647)
		return (NULL);
	ptr = (unsigned char *) malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	while (i < nmemb * size)
		ptr[i++] = 0;
	return (&ptr[0]);
}

size_t	gnl_strlen(const char *str)
{
	size_t	n;

	n = 0;
	if (!str)
		return (0);
	while (str && str[n])
		n++;
	return (n);
}

char	*gnl_strchr(const char *s, int c)
{
	int		i;
	char	*t;

	if (!s)
		return (NULL);
	t = (char *) s;
	i = 0;
	while (c >= 256)
		c -= 256;
	while (t[i])
	{
		if (t[i] == c)
			return (&t[i]);
		i++;
	}
	if (t[i] == 0 && c == '\0')
		return (&t[i]);
	return (NULL);
}

char	*gnl_strdup(const char *s)
{
	int		size;
	int		i;
	char	*t;

	i = 0;
	if (!s)
		return (NULL);
	size = (int) gnl_strlen(s);
	t = (char *) gnl_calloc(sizeof(char), size + 1);
	if (t == NULL)
		return (NULL);
	while (s[i])
	{
		t[i] = s[i];
		i++;
	}
	return (&t[0]);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	int		k;
	int		m;
	int		len;
	char	*new;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	m = 0;
	k = 0;
	new = NULL;
	len = gnl_strlen(s1) + gnl_strlen(s2);
	new = (char *) gnl_calloc (sizeof(char), len + 1);
	if (new == NULL)
		return (NULL);
	while (s1[k])
	{
		new[k] = s1[k];
		k++;
	}
	while (s2[m])
		new[k++] = s2[m++];
	return (new);
}
