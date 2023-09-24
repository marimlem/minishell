/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lknobloc <lknobloc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:05:21 by lknobloc          #+#    #+#             */
/*   Updated: 2023/07/24 14:53:35 by lknobloc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	size_t			k;
	char			*new;

	k = len;
	i = 0;
	j = 0;
	if (start >= (unsigned int) ft_strlen(s))
		k = 0;
	else if (len >= (size_t) ft_strlen(s))
		k = ft_strlen(&s[start]);
	new = (char *) malloc(sizeof(char) * (k + 1));
	if (new == NULL)
		return (NULL);
	while (i < start && s[i])
		i++;
	while (s[i] && j < len)
	{
		new[j] = s[i];
		i++;
		j++;
	}
	new[j] = 0;
	return (new);
}
/*
int	main()
{
	char	*str = "0123456789";
	int	start = 9;
	int	len = 10;
	
	char	*new = ft_substr(str, start, len);
	printf("%s\n", new);
	return 0;
}
*/
